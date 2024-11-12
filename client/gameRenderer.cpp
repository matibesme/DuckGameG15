#include "GameRenderer.h"
#include <algorithm> // para std::min y std::max
#include <QApplication>
#include <SDL_render.h>

#define IMAGE_CLOUDY_NIGHT DATA_PATH "/backgrounds/Cloudy night.png"
#define IMAGE_CITY DATA_PATH "/backgrounds/City.png"
#define IMAGE_FOREST DATA_PATH "/backgrounds/Forest.png"

#define CANT_ZOOM_WIDTH (7 * DUCK_WIDTH)
#define CANT_ZOOM_HEIGHT (15 * DUCK_HEIGHT)

GameRenderer::GameRenderer(Graficos &graficos, std::list<DTOPlatform> &platform)
    : graficos(graficos) {
  // Creo las plataformas por única vez
  for (auto &platformStruct : platform) {
    platforms.emplace_back(platformStruct.x_pos, platformStruct.y_pos, graficos,
                           platformStruct.type, platformStruct.width,
                           platformStruct.height);
  }
}

void GameRenderer::dibujar(Renderer &renderer, GameState &command) {
  if(command.action == VICTORY_BYTE){
    mostrarPantallaVictoria(command.name_winner);
    return;
  }else if (command.action == END_ROUND_BYTE) {
    mostrarPantallaEndRound(command.map_victorias);
    return;
  }

  // Limpio el renderizador y dibujar el fondo directamente en la pantalla
  renderer.SetTarget();
  renderer.Clear();
  drawBackground(command.backGround_id);

  // Creo una textura para dibujar todos los objetos
  SDL2pp::Texture textureDeTodo(renderer, SDL_PIXELFORMAT_RGBA8888,
                                SDL_TEXTUREACCESS_TARGET, SCENE_WIDTH,
                                SCENE_HEIGHT);

  // Habilito blending en la textura
  textureDeTodo.SetBlendMode(SDL_BLENDMODE_BLEND);

  // Cambio el objetivo de renderizado a textureDeTodo
  renderer.SetTarget(textureDeTodo);
  renderer.SetDrawColor(0, 0, 0,
                        0); // Limpio la textura con un color transparente
  renderer.Clear();

  // Dibujo los objetos en la textura
  for (auto &box : boxes)
    box.draw(renderer);
  for (auto &platform : platforms)
    platform.draw();
  for (auto &duck : ducks)
    duck.draw(renderer);
  for (auto &bullet : bullets)
    bullet.draw(renderer);
  for (auto &gun : guns)
    gun.draw(false, renderer);
  for (auto &armor : armors)
    armor.draw(false, renderer, false, false);
  for (auto &helmet : helmets)
    helmet.draw(false, renderer, false, false);


  // Vuelve al render principal
  renderer.SetTarget();

  // DESCOMENTAR PARA TENER ZOOM
  //  Defino el rectángulo de zoom para centrarse en la posición deseada
  SDL2pp::Rect srcRect = calcularRectanguloDeZoom(
      ducks); // Método que calcula el rectángulo para incluir todos los patos
  // Renderizar la textura con los objetos y zoom, sobre el fondo
  renderer.Copy(textureDeTodo, SDL2pp::Optional<SDL2pp::Rect>(srcRect),
                SDL2pp::Optional<SDL2pp::Rect>());

  // Por ahora no hago zoom renderer.Copy(textureDeTodo,
  // SDL2pp::Optional<SDL2pp::Rect>(), SDL2pp::Optional<SDL2pp::Rect>());
  //PantallaVictoria pantallaVictoria("patito", graficos);
  renderer.Present();
}

SDL2pp::Rect
GameRenderer::calcularRectanguloDeZoom(std::list<ClientDuck> &ducks) {
  if (ducks.empty()) {
    return {0, 0, 0, 0};
  }

  // Inicializo valores extremos con el primer pato
  int minX = ducks.front().getPosX();
  int maxX = minX;
  int minY = ducks.front().getPosY();
  int maxY = minY;

  // Encuentra las posiciones mínimas y máximas de los patos
  for (auto &duck : ducks) {
    minX = std::min(minX, duck.getPosX());
    maxX = std::max(maxX, duck.getPosX());
    minY = std::min(minY, duck.getPosY());
    maxY = std::max(maxY, duck.getPosY());
  }

  // Agregar un margen mínimo para evitar el estiramiento extremo
  const int MARGIN =
      50; // Define un margen mínimo que puedes ajustar según tu necesidad

  // Aseguramos que el rectángulo no se acerque demasiado a los bordes
  int width = maxX - minX + DUCK_WIDTH + CANT_ZOOM_WIDTH;
  int height = maxY - minY + DUCK_HEIGHT + CANT_ZOOM_HEIGHT;

  // Ajustamos el rectángulo de zoom con el margen mínimo
  int zoomWidth = std::max(width, MARGIN);
  int zoomHeight = std::max(height, MARGIN);

  // Ajustamos la posición del rectángulo para que no se salga de los bordes
  int zoomMinX = std::max(minX - CANT_ZOOM_WIDTH / 2, MARGIN);
  int zoomMinY = std::max(minY - CANT_ZOOM_HEIGHT / 2, MARGIN);

  //if(//pantalla el alto  && ancho){
    //proporcion de pantalla ratio tiene q tener el mismo ratio
    //si me quedo mucho mas anch que alto dibujo mas

  //}

  return {zoomMinX, zoomMinY, zoomWidth, zoomHeight};
}

void GameRenderer::actualizarElementos(const GameState &command) {
  // PRIMERO ACTUALIZO PATOS
  //  Actualizar y eliminar patos
  for (auto it = ducks.begin(); it != ducks.end();) {
    auto duckInCommand =
        std::find_if(command.lista_patos.begin(), command.lista_patos.end(),
                     [it](const DTODuck &duckStruct) {
                       return duckStruct.id == it->getId();
                     });
    if (duckInCommand != command.lista_patos.end()) {
      // Actualizar si el pato está en ambas listas
      it->update(duckInCommand->y_pos, duckInCommand->x_pos,
                 duckInCommand->typeOfMove, duckInCommand->typeOfGun,
                 duckInCommand->armor, duckInCommand->helmet,
                 duckInCommand->is_aiming_up, duckInCommand->direction);
      ++it;
    } else {
      // Eliminar si solo está en la lista local
      it = ducks.erase(it);
    }
  }

  // Agregar patos que están en el comando pero no en la lista local
  for (const auto &duckStruct : command.lista_patos) {
    auto it = std::find_if(ducks.begin(), ducks.end(),
                           [&duckStruct](const ClientDuck &duck) {
                             return duck.getId() == duckStruct.id;
                           });
    if (it == ducks.end()) {
      ducks.emplace_back(duckStruct.id, duckStruct.x_pos, duckStruct.y_pos,
                         duckStruct.typeOfGun, duckStruct.typeOfMove,
                         duckStruct.color, graficos);
    }
  }

  // SEGUNDO ACTUALIZO BALAS
  //  Agregar balas que están en el comando pero no en la lista local
  for (const auto &bulletStruct : command.lista_balas) {
    auto it = std::find_if(bullets.begin(), bullets.end(),
                           [&bulletStruct](const Bullet &bullet) {
                             return bullet.getId() == bulletStruct.id;
                           });
    if (it == bullets.end()) {
      bullets.emplace_back(bulletStruct.id, bulletStruct.x_pos,
                           bulletStruct.y_pos, graficos,
                           bulletStruct.orientation, bulletStruct.typeOfBullet);
    }
  }

  // Actualizar y eliminar balas
  for (auto it = bullets.begin(); it != bullets.end();) {
    auto bulletInCommand =
        std::find_if(command.lista_balas.begin(), command.lista_balas.end(),
                     [it](const DTOBullet &bulletStruct) {
                       return bulletStruct.id == it->getId();
                     });
    if (bulletInCommand != command.lista_balas.end()) {
      // Actualizar si la bala está en ambas listas
      it->update(bulletInCommand->x_pos, bulletInCommand->y_pos,
                 bulletInCommand->typeOfBullet, bulletInCommand->orientation);
      ++it;
    } else {
      // Eliminar si solo está en la lista local
      it = bullets.erase(it);
    }
  }

  // TERCERO ACTUALIZO ARMAS
  for (auto it = guns.begin(); it != guns.end();) {
    auto weaponInCommand =
        std::find_if(command.lista_guns.begin(), command.lista_guns.end(),
                     [it](const DTOGuns &weaponStruct) {
                       return weaponStruct.x_pos == it->getPosX() &&
                              weaponStruct.y_pos == it->getPosY();
                     });
    if (weaponInCommand != command.lista_guns.end()) {
      // Actualizar si el arma está en ambas listas
      ++it;
    } else {
      // Eliminar si solo está en la lista local
      it = guns.erase(it);
    }
  }

  // Agregar armas que están en el comando pero no en la lista local
  for (const auto &weaponStruct : command.lista_guns) {
    auto it =
        std::find_if(guns.begin(), guns.end(), [&weaponStruct](Gun &weapon) {
          return weapon.getPosX() == weaponStruct.x_pos &&
                 weapon.getPosY() == weaponStruct.y_pos;
        });
    if (it == guns.end()) {
      guns.emplace_back(graficos, weaponStruct.x_pos, weaponStruct.y_pos,
                        weaponStruct.typeOfGun);
    }
  }

  // CUARTO ACTUALIZO ARMADURAS
  for (auto it = armors.begin(); it != armors.end();) {
    auto armorInCommand =
        std::find_if(command.lista_armors.begin(), command.lista_armors.end(),
                     [it](const Protection &armorStruct) {
                       return armorStruct.x_pos == it->getPosX() &&
                              armorStruct.y_pos == it->getPosY();
                     });
    if (armorInCommand != command.lista_armors.end()) {
      // Actualizar si el arma está en ambas listas
      ++it;
    } else {
      // Eliminar si solo está en la lista local
      it = armors.erase(it);
    }
  }

  // Agregar armaduras que están en el comando pero no en la lista local
  for (const auto &armorStruct : command.lista_armors) {
    auto it = std::find_if(armors.begin(), armors.end(),
                           [&armorStruct](Armor &armor) {
                             return armor.getPosX() == armorStruct.x_pos &&
                                    armor.getPosY() == armorStruct.y_pos;
                           });
    if (it == armors.end()) {
      armors.emplace_back(graficos, armorStruct.x_pos, armorStruct.y_pos);
    }
  }

  // QUINTO ACTUALIZO CASCOS
  for (auto it = helmets.begin(); it != helmets.end();) {
    auto helmetInCommand =
        std::find_if(command.lista_helmets.begin(), command.lista_helmets.end(),
                     [it](const Protection &helmetStruct) {
                       return helmetStruct.x_pos == it->getPosX() &&
                              helmetStruct.y_pos == it->getPosY();
                     });
    if (helmetInCommand != command.lista_helmets.end()) {
      // Actualizar si el arma está en ambas listas
      ++it;
    } else {
      // Eliminar si solo está en la lista local
      it = helmets.erase(it);
    }
  }

  // Agregar cascos que están en el comando pero no en la lista local
  for (const auto &helmetStruct : command.lista_helmets) {
    auto it = std::find_if(helmets.begin(), helmets.end(),
                           [&helmetStruct](Helmet &helmet) {
                             return helmet.getPosX() == helmetStruct.x_pos &&
                                    helmet.getPosY() == helmetStruct.y_pos;
                           });
    if (it == helmets.end()) {
      helmets.emplace_back(graficos, helmetStruct.x_pos, helmetStruct.y_pos);
    }
  }

  // SEXTO ACTUALIZO CAJAS
  for (auto it = boxes.begin(); it != boxes.end();) {
    auto boxInCommand =
        std::find_if(command.lista_boxes.begin(), command.lista_boxes.end(),
                     [it](const DTOBoxes &boxStruct) {
                       return boxStruct.id == it->getId();
                     });
    if (boxInCommand != command.lista_boxes.end()) {
      // Actualizar si la caja está en ambas listas
      ++it;
    } else {
      // Eliminar si solo está en la lista local
      it = boxes.erase(it);
    }
  }

  // Agregar cajas que están en el comando pero no en la lista local
  for (const auto &boxStruct : command.lista_boxes) {
    auto it = std::find_if(boxes.begin(), boxes.end(), [&boxStruct](Box &box) {
      return box.getId() == boxStruct.id;
    });
    if (it == boxes.end()) {
      boxes.emplace_back(boxStruct.id, boxStruct.x_pos, boxStruct.y_pos,
                         graficos);
    }
  }
}

void GameRenderer::drawBackground(const uint8_t background_id) {
  Renderer &renderer = graficos.GetRenderer();

  // creo una textura vacía para dibujar el fondo
  SDL2pp::Texture background(renderer, SDL_PIXELFORMAT_RGBA8888,
                             SDL_TEXTUREACCESS_TARGET, SCENE_WIDTH,
                             SCENE_HEIGHT);

  // Cargar y dibujar el fondo
  if (background_id == TYPE_BACKGROUND_CIELO_NUBES) {
    background = graficos.LoadTexture(IMAGE_CLOUDY_NIGHT);
  } else if (background_id == TYPE_BACKGROUND_CITY) {
    background = graficos.LoadTexture(IMAGE_CITY);
  } else if (background_id == TYPE_BACKGROUND_FOREST) {
    background = graficos.LoadTexture(IMAGE_FOREST);
  }

  renderer.Copy(background, SDL2pp::NullOpt, SDL2pp::NullOpt);
}

void GameRenderer::mostrarPantallaVictoria(std::string &winner) {
  char* args[] = { (char*)"AppName" };
  int argc_ = 1;
  QApplication a(argc_, args);
  FinalScene w(winner);
  w.show();
  a.exec();
}

void GameRenderer::mostrarPantallaEndRound(std::map<std::string, uint8_t> &map_victorias) {
  char* args[] = { (char*)"AppName" };
  int argc_ = 1;
  QApplication a(argc_, args);
  EndRoundScene w(map_victorias);
  w.show();
  a.exec();
}

