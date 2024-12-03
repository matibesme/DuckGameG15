//
// Created by ezequiel on 03/12/24.
//

#include "colisions.h"
#include <iostream>
#include <memory>

Colisions::Colisions(std::list<DTOPlatform> &list_plataformas,
                     std::map<uint8_t, DuckPlayer> &map_personajes,
                     std::vector<std::string> &list_colors,
                     std::list<DuckPlayer> &dead_players,
                     std::list<Boxes> &list_boxes,
                     std::map<uint16_t, std::unique_ptr<Bullet>> &map_bullets)
    : list_plataformas(list_plataformas), map_personajes(map_personajes),
      list_colors(list_colors), dead_players(dead_players),
      list_boxes(list_boxes), map_bullets(map_bullets) {}

void Colisions::checkCoalitionDuckPlatform(DuckPlayer &personaje) {
  bool is_on_platform = false;
  for (auto &platform : list_plataformas) {
    if (sobrePlataformaX(personaje, platform)) {
      bool is_on_platform_down = false;
      coalisionSuperiorEinferior(personaje, platform, is_on_platform,
                                 is_on_platform_down);
      if (is_on_platform_down)
        return;
    }
    coalisonWalls(personaje, platform);
  }

  if (!is_on_platform && (!personaje.estaSaltando() || personaje.isSliding())) {
    personaje.setRespondAfterSliding(15);
    personaje.setIsSliding(false);
    personaje.setEnSalto(true);
    personaje.setVelocidadY(CERO);
  }
}

bool Colisions::sobrePlataformaX(const DuckPlayer &personaje,
                                 const DTOPlatform &platform) {
  return (personaje.getXPos() >= platform.x_pos &&
          personaje.getXPos() <=
              platform.x_pos + platform.width - MARGEN_DESPLAZAMIENTO_PATO_X) ||
         (personaje.getXPos() <= platform.x_pos &&
          personaje.getXPos() + (DUCK_WIDTH - MARGEN_DESPLAZAMIENTO_PATO_X) >=
              platform.x_pos) ||
         (personaje.getXPos() <=
              platform.x_pos + platform.width - MARGEN_DESPLAZAMIENTO_PATO_X &&
          personaje.getXPos() + DUCK_WIDTH - MARGEN_DESPLAZAMIENTO_PATO_X >=
              platform.x_pos + platform.width - MARGEN_DESPLAZAMIENTO_PATO_X);
}

void Colisions::coalisionSuperiorEinferior(DuckPlayer &personaje,
                                           const DTOPlatform &platform,
                                           bool &is_on_platform,
                                           bool &is_on_platform_down) {
  if (personaje.getYPos() + DUCK_HEIGHT >=
          platform.y_pos - PLATAFORMA_LEVEMENTE_LEVANTADA &&
      personaje.getYPos() + personaje.getVelocidadY() <= platform.y_pos) {
    if (personaje.getVelocidadY() < CERO) {
      personaje.stopJump(platform.y_pos - DUCK_HEIGHT);
    } else {
      personaje.setYPos(platform.y_pos - DUCK_HEIGHT);
    }
    is_on_platform = true;
  }
  if (personaje.getYPos() <= platform.y_pos + platform.height &&
      personaje.getYPos() + DUCK_HEIGHT > platform.y_pos + platform.height &&
      personaje.getVelocidadY() > CERO) {
    if (personaje.getXPos() >= platform.x_pos + platform.width -
                                   MARGEN_DESPLAZAMIENTO_PLATAFORMA_X_IZQ) {
      return;
    }
    personaje.setYPos(platform.y_pos + platform.height);
    personaje.setVelocidadY(CERO);
    is_on_platform_down = true;
  }
}

void Colisions::coalisonWalls(DuckPlayer &personaje,
                              const DTOPlatform &platform) {
  if (personaje.getYPos() + DUCK_HEIGHT - DUCK_HEIGHT / 3 > platform.y_pos &&
      personaje.getYPos() < platform.y_pos + platform.height) {
    if (personaje.isWeaponEquipped()) {
      if (personaje.getXPos() + DUCK_WIDTH - DESPLAZAMIENTO_CON_ARMA_X >
              platform.x_pos &&
          personaje.getXPos() < platform.x_pos &&
          personaje.getDirection() == RIGHT) {
        personaje.setXPos(platform.x_pos - DUCK_WIDTH +
                          DESPLAZAMIENTO_CON_ARMA_X);
      } else if (personaje.getXPos() - MARGEN_DESPLAZAMIENTO_PLATAFORMA_X <
                     platform.x_pos + platform.width -
                         MARGEN_DESPLAZAMIENTO_PLATAFORMA_X &&
                 personaje.getXPos() - MARGEN_DESPLAZAMIENTO_PLATAFORMA_X >
                     platform.x_pos &&
                 personaje.getDirection() == LEFT) {
        personaje.setXPos(platform.x_pos + platform.width);
      }
      return;
    }

    if (personaje.getXPos() + DUCK_WIDTH - MARGEN_DESPLAZAMIENTO_PATO_X_WALL >
            platform.x_pos &&
        personaje.getXPos() < platform.x_pos &&
        personaje.getDirection() == RIGHT) {
      personaje.setXPos(platform.x_pos - DUCK_WIDTH +
                        MARGEN_DESPLAZAMIENTO_PATO_X_WALL);
    } else if (personaje.getXPos() - 4 <
                   platform.x_pos + platform.width -
                       MARGEN_DESPLAZAMIENTO_PLATAFORMA_X &&
               personaje.getXPos() > platform.x_pos &&
               personaje.getDirection() == LEFT) {
      personaje.setXPos(platform.x_pos + platform.width -
                        MARGEN_DESPLAZAMIENTO_PLATAFORMA_X);
    }
  }
}

void Colisions::checkCoalition(std::unique_ptr<Bullet> &bullet) {
  for (auto &plataform : list_plataformas) {
    bullet->colisionWithPlatform(plataform.x_pos, plataform.y_pos,
                                 plataform.width, plataform.height + 5);
  }
  uint8_t bullet_type = bullet->getTypeOfBullet();
  if (bullet_type != GRANADA_BULLET && bullet_type != GRENADE_EXPLOSION) {
    for (auto it = map_personajes.begin(); it != map_personajes.end();) {
      bool colision;
      if (it->second.getTypeOfMoveSprite() == DOWN) {
        colision = bullet->colisionWithDuck(
            it->second.getXPos() - (DUCK_HEIGHT / 2),
            it->second.getYPos() + DUCK_HEIGHT - DUCK_DOWN_HEIGHT, DUCK_HEIGHT,
            DUCK_WIDTH);
      } else {
        colision =
            bullet->colisionWithDuck(it->second.getXPos(), it->second.getYPos(),
                                     DUCK_WIDTH, DUCK_HEIGHT);
      }
      if (colision) {
        if (bullet_type == BANANA_BULLET) {
          it->second.setIsSliding(true);
          return;
        }
        if (it->second.receiveShoot()) {
          it->second.applyDamage(bullet->getDamage());
          it->second.setColor(list_colors.back());
        }
        if (!it->second.isAlive()) {
          dead_players.push_back(it->second);
          it = map_personajes.erase(it);
        } else {
          ++it;
        }
        return;
      } else {
        ++it;
      }
    }
  }

  for (auto it = list_boxes.begin(); it != list_boxes.end();) {
    bool colision = bullet->colisionWithBox(it->getXPos(), it->getYPos(),
                                            WIDTH_BOX, HEIGHT_BOX);
    if (colision) {
      it->takeDamage(bullet->getDamage());
      if (it->isDestroyed()) {
        it = list_boxes.erase(it);
        break;
      } else {
        ++it;
      }
    } else {
      ++it;
    }
  }
}

void Colisions::checkGrenadeExplosion(GranadaBullet &grenade_bullet) {
  grenade_bullet.setIsExplode(true);
  for (auto it = map_personajes.begin(); it != map_personajes.end();) {
    if (grenade_bullet.getXPos() - (RADIO_EXPLOTION_GRANADA * DUCK_WIDTH) <
            it->second.getXPos() &&
        grenade_bullet.getXPos() + (RADIO_EXPLOTION_GRANADA * DUCK_WIDTH) >
            it->second.getXPos() &&
        grenade_bullet.getYPos() - (RADIO_EXPLOTION_GRANADA * DUCK_HEIGHT) <
            it->second.getYPos() &&
        grenade_bullet.getYPos() + (RADIO_EXPLOTION_GRANADA * DUCK_HEIGHT) >
            it->second.getYPos()) {
      if (it->second.receiveShoot()) {
        it->second.applyDamage(grenade_bullet.getDamage());
        it->second.setColor(list_colors.back());
      }
      if (!it->second.isAlive()) {
        dead_players.push_back(it->second);
        it = map_personajes.erase(it);
      } else {
        ++it;
      }
    } else {
      ++it;
    }
  }
  for (auto it = list_boxes.begin(); it != list_boxes.end();) {
    if (grenade_bullet.getXPos() - (RADIO_EXPLOTION_GRANADA * WIDTH_BOX) <
            it->getXPos() &&
        grenade_bullet.getXPos() + (RADIO_EXPLOTION_GRANADA * WIDTH_BOX) >
            it->getXPos() &&
        grenade_bullet.getYPos() - (RADIO_EXPLOTION_GRANADA * HEIGHT_BOX) <
            it->getYPos() &&
        grenade_bullet.getYPos() + (RADIO_EXPLOTION_GRANADA * HEIGHT_BOX) >
            it->getYPos()) {
      it->takeDamage(grenade_bullet.getDamage());
      if (it->isDestroyed()) {
        it = list_boxes.erase(it);
      } else {
        ++it;
      }
    } else {
      ++it;
    }
  }
}

void Colisions::checkBullets() {
  for (auto it = map_bullets.begin(); it != map_bullets.end();) {
    if (!it->second->isAlive()) {
      if (it->second->getTypeOfBullet() == GRENADE_EXPLOSION) {
        GranadaBullet *grenadeBullet =
            dynamic_cast<GranadaBullet *>(it->second.get());
        if (grenadeBullet) {
          checkGrenadeExplosion(*grenadeBullet);
        } else {
          std::cerr << "Error: Tipo incorrecto para GRENADE_EXPLOSION\n";
        }
      }
      it = map_bullets.erase(it);
    } else {
      checkCoalition(it->second);
      it->second->executeAction();
      ++it;
    }
  }
}
