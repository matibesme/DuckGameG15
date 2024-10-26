//
// Created by matibesme on 24/10/24.
//

#ifndef BULLET_PISTOLA_COWBOY_H
#define BULLET_PISTOLA_COWBOY_H
#include "bullet.h"
#include "../../constant_definitons.h"

class CowBoyBullet : public Bullet {

public:
    CowBoyBullet(uint8_t type, uint8_t id, float x_pos, float y_pos, uint8_t damage, uint8_t range, float spread);

    void executeAction() override;

};



#endif //BULLET_PISTOLA_COWBOY_H
