//
// Created by ezequiel on 07/11/24.
//

#include "boxes.h"

#include <cstdlib>
#include <ctime>

#include "weapons/factory_weapons.h"

Boxes::Boxes(uint8_t type, uint8_t id, float x_pos, float y_pos, int health,
             std::map<uint16_t, std::shared_ptr<Weapon>> &map_free_weapons,
             std::map<uint16_t, Protection> &map_defense,
             std::map<uint16_t, std::unique_ptr<Bullet>> &map_bullets,
             uint16_t &id_balas, uint16_t &id_weapons, uint16_t &id_defense)
    : Objeto(type, id, x_pos, y_pos), health(health),
      map_free_weapons(map_free_weapons), map_defense(map_defense),
      map_bullets(map_bullets), id_balas(id_balas), id_weapons(id_weapons),
      id_defense(id_defense) {}

void Boxes::takeDamage(int damage) {
  health -= damage;
  if (isDestroyed()) {
    generateRandomContent();
  }
}

bool Boxes::isDestroyed() const { return health <= 0; }

void Boxes::generateRandomContent() {
  srand(time(NULL));
  int random_number = rand() % 5 + 1;
  FactoryWeapons factory_weapons;
  switch (random_number) {
  case 1:
    break;
  case 2:
    map_free_weapons.emplace(id_weapons++,
                             factory_weapons.generateRandomWeapon(
                                 x_pos, y_pos + HEIGHT_BOX - HEIGHT_GUN));
    break;
  case 3:
    map_defense.emplace(
        id_defense++,
        Protection{ARMOR_EQUIPPED, x_pos, y_pos + HEIGHT_BOX - HEIGHT_ARMOR});
    break;
  case 4:
    map_defense.emplace(
        id_defense++,
        Protection{HELMET_EQUIPPED, x_pos, y_pos + HEIGHT_BOX - HEIGHT_HELMET});
    break;
  case 5:

    map_bullets.emplace(
        id_balas++, std::move(factory_weapons
                                  .createWeapon(GRANADA_GUN, x_pos,
                                                y_pos + HEIGHT_BOX - HEIGHT_GUN)
                                  ->shoot(false)));
  default:
    break;
  }
}
