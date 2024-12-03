//
// Created by ezequiel on 03/12/24.
//

#ifndef COLISIONS_H
#define COLISIONS_H
#include "../common/dto_definitions.h"
#include "items/boxes.h"
#include "items/bullets/bullet.h"
#include "items/bullets/granada_bullet.h"
#include "items/ducks/duck.h"
#include "items/weapons/weapon.h"
#include "server_constant.h"
#include <list>
#include <map>
#include <memory>
#include <string>
#include <vector>

class Colisions {
private:
  std::list<DTOPlatform> &list_plataformas;
  std::map<uint8_t, DuckPlayer> &map_personajes;
  std::vector<std::string> &list_colors;
  std::list<DuckPlayer> &dead_players;
  std::list<Boxes> &list_boxes;
  std::map<uint16_t, std::unique_ptr<Bullet>> &map_bullets;

public:
  Colisions(std::list<DTOPlatform> &list_plataformas,
            std::map<uint8_t, DuckPlayer> &map_personajes,
            std::vector<std::string> &list_colors,
            std::list<DuckPlayer> &dead_players, std::list<Boxes> &list_boxes,
            std::map<uint16_t, std::unique_ptr<Bullet>> &map_bullets);
  void checkCoalition(std::unique_ptr<Bullet> &bullet);
  void checkCoalitionDuckPlatform(DuckPlayer &personaje);
  void coalisionSuperiorEinferior(DuckPlayer &personaje,
                                  const DTOPlatform &platform,
                                  bool &is_on_platform,
                                  bool &is_on_platform_down);
  void coalisonWalls(DuckPlayer &personaje, const DTOPlatform &platform);
  bool sobrePlataformaX(const DuckPlayer &personaje,
                        const DTOPlatform &platform);
  void checkGrenadeExplosion(GranadaBullet &grenade_bullet);
  void checkBullets();
};

#endif // COLISIONS_H
