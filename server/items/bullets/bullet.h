//
// Created by matibesme on 24/10/24.
//

#ifndef BULLET_H
#define BULLET_H
#include "../objeto.h"
#include <cstdint>
#include "server_constant.h"

class Bullet: public Objeto {
    protected:
        uint8_t damage;
        uint8_t range;
        bool is_alive;
        float spread;
        bool spread_direction;



    public:
        Bullet(uint8_t type, uint8_t id, float x_pos, float y_pos, uint8_t damage, uint8_t range, float spread);
        uint8_t getDamage();
        uint8_t getRange();
        virtual void colisionWithPlatform(float plat_x_pos, float plat_y_pos, float plat_width, float plat_height);
        uint8_t getTypeOfBullet();
        bool isAlive();
        void release(float x_pos, float y_pos, uint8_t direction);
        bool randomSpread();
        virtual void executeAction();
        void kill();

};


#endif //BULLET_H
