// Created by ezequiel on 07/11/24.
//

#ifndef BOXES_H
#define BOXES_H

#include "objeto.h"

#include "dto_definitions.h"
#include "weapons/granada.h"
#include "weapons/weapon.h"
#include <map>
#include <memory>
#include <random>
#include <variant>

class Boxes : public Objeto {
private:
  int health;
  std::map<uint16_t, std::shared_ptr<Weapon>> &map_free_weapons;
  std::map<uint16_t, Protection> &map_defense;
  std::map<uint16_t, std::unique_ptr<Bullet>> &map_bullets;
  uint16_t &id_balas;
  uint16_t &id_weapons;
  uint16_t &id_defense;

  void generateRandomContent();

public:
  Boxes(uint8_t type, uint8_t id, float x_pos, float y_pos, int health,
        std::map<uint16_t, std::shared_ptr<Weapon>> &map_free_weapons,
        std::map<uint16_t, Protection> &map_defense,
        std::map<uint16_t, std::unique_ptr<Bullet>> &map_bullets,
        uint16_t &id_balas, uint16_t &id_weapons, uint16_t &id_defense);

  void takeDamage(int damage);

  bool isDestroyed() const;
};

#endif // BOXES_H
