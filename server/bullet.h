//
// Created by matibesme on 24/10/24.
//

#ifndef BULLET_H
#define BULLET_H
#include "objeto.h"
#include <cstdint>

class Bullet: public Objeto {
    protected:
        uint8_t damage;
        uint8_t range;
        bool is_alive;


    public:
        Bullet(uint8_t type, uint8_t id, float x_pos, float y_pos, uint8_t damage, uint8_t range);
        uint8_t getDamage();
        uint8_t getRange();

        uint8_t getTypeOfBullet();
        bool isAlive();
        virtual void release(float x_pos, float y_pos, uint8_t direction);
        virtual void executeAction();
        virtual ~Bullet();
};



#endif //BULLET_H
