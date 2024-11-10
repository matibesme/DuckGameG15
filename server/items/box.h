// Created by ezequiel on 07/11/24.
//

#ifndef BOX_H
#define BOX_H


#include "objeto.h"

#include <memory>
#include <map>
#include <random>
#include <variant>
#include "weapons/weapon.h"
#include "weapons/granada.h"
#include  "dto_definitions.h"

class Box : public Objeto {
private:
    int health;
    std::map<uint16_t,std::shared_ptr<Weapon>>& map_free_weapons;
    std::map<uint8_t, Protection>& map_armor;
    std::map<uint8_t, Protection>& map_helmet;
    std::map<uint16_t, std::unique_ptr<Bullet>>& map_bullets;
    uint16_t& id_balas;
    uint16_t& id_weapons;


    void generateRandomContent();

public:
    Box(uint8_t type, uint8_t id, float x_pos, float y_pos, int health, std::map<uint16_t,
        std::shared_ptr<Weapon>>& map_free_weapons, std::map<uint8_t, Protection>& map_armor, std::map<uint8_t, Protection>& map_helmet,
        std::map<uint16_t, std::unique_ptr<Bullet>>& map_bullets, uint16_t& id_balas, uint16_t& id_weapons);

    void takeDamage(int damage);

    bool isDestroyed() const;


};

#endif //BOX_H
