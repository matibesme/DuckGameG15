//
// Created by matibesme on 24/10/24.
//

#ifndef BULLET_H
#define BULLET_H
#include "../objeto.h"
#include <cstdint>
#include "../../constant_definitons.h"

class Bullet: public Objeto {
    protected:
        uint8_t damage;
        uint8_t range;
        bool is_alive;
        float spread;


    public:
        Bullet(uint8_t type, uint8_t id, float x_pos, float y_pos, uint8_t damage, uint8_t range, float spread);
        uint8_t getDamage();
        uint8_t getRange();

        uint8_t getTypeOfBullet();
        bool isAlive();
        void release(float x_pos, float y_pos, uint8_t direction);
        void executeAction();
        void kill();

};


#endif //BULLET_H
