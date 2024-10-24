//
// Created by matibesme on 24/10/24.
//

#ifndef BULLET_PISTOLA_COWBOY_H
#define BULLET_PISTOLA_COWBOY_H
#include "weapon.h"


class CowBoyBullet : public Bullet {
public:
    CowBoyBullet();
    void executeAction() override;
    ~CowBoyBullet() override;
};



#endif //BULLET_PISTOLA_COWBOY_H
