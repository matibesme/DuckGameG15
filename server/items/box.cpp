//
// Created by ezequiel on 07/11/24.
//

#include "box.h"
#include "weapons/factory_weapons.h"
#include <cstdlib>
#include <ctime>

/*
Box::Box(uint8_t type, uint8_t id, float x_pos, float y_pos, int health,
    std::map<uint16_t,std::shared_ptr<Weapon>>& map_free_weapons, std::map<uint8_t, Protection>& map_armor, std::map<uint8_t, Protection>& map_helmet,
    std::map<uint16_t, std::unique_ptr<Bullet>>& map_bullets, uint16_t& id_balas, uint16_t& id_weapons):
        Objeto(type, id, x_pos, y_pos),
        health(health),
        map_free_weapons(map_free_weapons),
        map_armor(map_armor),
        map_helmet(map_helmet),
        map_bullets(map_bullets),
        id_balas(id_balas),
        id_weapons(id_weapons) {}

void Box::takeDamage(int damage) {
        health -= damage;
        if (isDestroyed()) {
            generateRandomContent();
        }
}

bool Box::isDestroyed() const {
    return health <= 0;
}

void Box::generateRandomContent() {
    std::srand(std::time(0));
    int random_number = std::rand() % 5 + 1;
    FactoryWeapons factory_weapons;
    switch (random_number) {
        case 1:
            break;
        case 2:
            std::shared_ptr<Weapon> weapon = factory_weapons.generateRandomWeapon(x_pos, y_pos);
            map_free_weapons.emplace(id_weapons++, weapon);
            break;
        case 3:
            map_armor.emplace(1, Protection{1, x_pos, y_pos});
            break;
        case 4:
            map_helmet.emplace(1, Protection{1, x_pos, y_pos});
            break;
        case 5:
            std::shared_ptr<Weapon> granada = std::make_shared<Granada>(GRANADA_GUN, 1, x_pos, y_pos, 10, 38, 100, 0);
            std::unique_ptr<Bullet> explosion = granada->shoot();
            map_bullets.emplace(id_balas++, std::move(explosion));
        default:
            break;

    }
}

*/