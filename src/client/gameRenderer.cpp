#include "GameRenderer.h"
#include <QApplication>
#include <SDL_render.h>
#include <algorithm> // para std::min y std::max

#define IMAGE_CLOUDY_NIGHT DATA_PATH "/backgrounds/Cloudy night.png"
#define IMAGE_River DATA_PATH "/backgrounds/River.png"
#define IMAGE_FOREST DATA_PATH "/backgrounds/Forest.png"

GameRenderer::GameRenderer(Graficos &graficos) : graficos(graficos) {}

void GameRenderer::dibujar(Renderer &renderer, GameState &command) {
  // Limpio el renderizador y dibujo el fondo directamente en la pantalla
  renderer.SetTarget();
  renderer.Clear();

  // Dibujo el fondo
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
    gun.drawOnSpawn(renderer);
  for (auto &armor : armors)
    armor.draw(false, renderer, false, false);
  for (auto &helmet : helmets)
    helmet.draw(false, renderer, false, false);

  // Vuelve al render principal
  renderer.SetTarget();

  // Calcular el rectángulo de zoom
  SDL2pp::Rect srcRect = calcularRectanguloDeZoom(ducks);

  // Escalar la textura para que ocupe todo el ancho y alto de la pantalla
  SDL2pp::Rect dstRect(0, 0, SCENE_WIDTH, SCENE_HEIGHT);

  // Renderizar la textura con zoom aplicado sobre toda la pantalla
  renderer.Copy(textureDeTodo, SDL2pp::Optional<SDL2pp::Rect>(srcRect),
                SDL2pp::Optional<SDL2pp::Rect>(dstRect));

  renderer.Present();
}

SDL2pp::Rect
GameRenderer::calcularRectanguloDeZoom(std::list<ClientDuck> &ducks) {
  if (ducks.empty()) {
    return {0, 0, SCENE_WIDTH, SCENE_HEIGHT};
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

  // Márgenes para evitar ajustes pequeños innecesarios
  constexpr int MARGIN = 100; // Ajusta según tu preferencia

  // Agregar margen alrededor de los patos
  minX -= MARGIN;
  maxX += MARGIN;
  minY -= MARGIN;
  maxY += MARGIN;

  // Calcular el tamaño del área ocupada por los patos
  int width = maxX - minX;
  int height = maxY - minY;

  // Asegurar que el rectángulo sea cuadrado manteniendo un ratio constante
  constexpr float SCENE_RATIO = static_cast<float>(SCENE_WIDTH) / SCENE_HEIGHT;

  if (width > height * SCENE_RATIO) {
    // El ancho domina, ajustamos la altura
    height = static_cast<int>(width / SCENE_RATIO);
  } else {
    // La altura domina, ajustamos el ancho
    width = static_cast<int>(height * SCENE_RATIO);
  }

  // Centrar el rectángulo alrededor de los patos
  int centerX = (minX + maxX) / 2;
  int centerY = (minY + maxY) / 2;

  // Permitir que el rectángulo de zoom se salga de los límites de los patos y
  // muestre más fondo
  int zoomMinX = centerX - width / 2;
  int zoomMinY = centerY - height / 2;

  // Permitir que el zoom "salga" de los límites del mapa, sin restringirlo
  // No limitamos las coordenadas mínimas ni máximas
  zoomMinX = std::max(zoomMinX, 0); // No puede ser menor que 0
  zoomMinY = std::max(zoomMinY, 0); // No puede ser menor que 0

  // Ampliamos el área de fondo permitiendo que el zoom se extienda más allá del
  // mapa
  int zoomMaxX = zoomMinX + width;
  int zoomMaxY = zoomMinY + height;

  // De nuevo, sin restringir el tamaño a los límites del mapa
  // No hay límite superior para zoomMaxX ni zoomMaxY

  // Ajustar el tamaño del rectángulo para que se mantenga cuadrado
  width = zoomMaxX - zoomMinX;
  height = zoomMaxY - zoomMinY;

  return {zoomMinX, zoomMinY, width, height};
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
      // Actualizar si la armadura está en ambas listas
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
      // Actualizar si el casco está en ambas listas
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
    auto boxInCommand = std::find_if(
        command.lista_boxes.begin(), command.lista_boxes.end(),
        [it](const DTOBoxes &boxStruct) {
          return boxStruct.x_pos == it->getX() && boxStruct.y_pos == it->getY();
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
      return box.getX() == boxStruct.x_pos && box.getY() == boxStruct.y_pos;
    });
    if (it == boxes.end()) {
      boxes.emplace_back(boxStruct.id, boxStruct.x_pos, boxStruct.y_pos,
                         graficos);
    }
  }

  // SEPTIMO ACTUALIZO PLATAFORMAS
  for (auto it = platforms.begin(); it != platforms.end();) {
    auto platformInCommand = std::find_if(
        command.lista_plataformas.begin(), command.lista_plataformas.end(),
        [it](const DTOPlatform &platformStruct) {
          return platformStruct.x_pos == it->getX() &&
                 platformStruct.y_pos == it->getY();
        });
    if (platformInCommand != command.lista_plataformas.end()) {
      // Actualizar si la plataforma está en ambas listas
      ++it;
    } else {
      // Eliminar si solo está en la lista local
      it = platforms.erase(it);
    }
  }

  // Agregar plataformas que están en el comando pero no en la lista local
  for (const auto &platformStruct : command.lista_plataformas) {
    auto it = std::find_if(platforms.begin(), platforms.end(),
                           [&platformStruct](Platform &platform) {
                             return platform.getX() == platformStruct.x_pos &&
                                    platform.getY() == platformStruct.y_pos;
                           });
    if (it == platforms.end()) {
      platforms.emplace_back(platformStruct.x_pos, platformStruct.y_pos,
                             graficos, platformStruct.type,
                             platformStruct.width, platformStruct.height);
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
    background = graficos.LoadTexture(IMAGE_River);
  } else if (background_id == TYPE_BACKGROUND_FOREST) {
    background = graficos.LoadTexture(IMAGE_FOREST);
  }

  renderer.Copy(background, SDL2pp::NullOpt, SDL2pp::NullOpt);
}

void GameRenderer::mostrarPantallaColores(
    std::map<std::string, std::string> &playersColors, Renderer &renderer) {
  // Castear el renderer de SDL2pp a SDL_Renderer& y pasarlo al constructor
  SDL_Renderer &sdlRenderer =
      *renderer.Get(); // Obtiene el SDL_Renderer subyacente
  ColorScene colorScene(playersColors,
                        sdlRenderer); // Pasar el SDL_Renderer a la escena
  colorScene.Run();                   // Ejecutar la escena
}

void GameRenderer::mostrarPantallaVictoria([[maybe_unused]] std::string &winner,
                                           Renderer &renderer) {
  // Castear el renderer de SDL2pp a SDL_Renderer& y pasarlo al constructor
  SDL_Renderer &sdlRenderer =
      *renderer.Get(); // Obtiene el SDL_Renderer subyacente
  FinalScene finalScene(winner,
                        sdlRenderer); // Pasar el SDL_Renderer a la escena
  finalScene.Render();                // Ejecutar la escena
}

void GameRenderer::mostrarPantallaEndRound(
    std::map<std::string, uint8_t> &map_victorias, Renderer &renderer) {
  // Castear el renderer de SDL2pp a SDL_Renderer& y pasarlo al constructor
  SDL_Renderer &sdlRenderer =
      *renderer.Get(); // Obtiene el SDL_Renderer subyacente
  EndRoundScene endRoundSene(map_victorias,
                             sdlRenderer); // Pasar el SDL_Renderer a la escena
  endRoundSene.Run();                      // Ejecutar la escena
}

// destructores
GameRenderer::~GameRenderer() {
  ducks.clear();
  bullets.clear();
  guns.clear();
  armors.clear();
  helmets.clear();
  platforms.clear();
  boxes.clear();
}
