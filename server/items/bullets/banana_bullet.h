//
// Created by matibesme on 30/10/24.
//

#ifndef BANANA_BULLET_H
#define BANANA_BULLET_H
#include "../../constant_definitons.h"
#include "bullet.h"


class BananaBullet : public Bullet {
private:
    float velocidad;
    bool continue_moving;
public:
    BananaBullet(uint8_t type, uint8_t id, float x_pos, float y_pos, uint8_t damage, uint8_t range, float spread);
    void executeAction() override;

};




#endif //BANANA_BULLET_H
