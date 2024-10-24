//
// Created by matibesme on 24/10/24.
//

#ifndef BULLET_PISTOLA_COWBOY_H
#define BULLET_PISTOLA_COWBOY_H
#include "weapon.h"

enum Direccion {
    ARRIBA = 50,
    IZQUIERDA = 51,
    DERECHA = 52
};

class CowBoyBullet : public Bullet {
private:
    Direccion direction;
public:
    CowBoyBullet(uint8_t type, uint8_t id, float x_pos, float y_pos, uint8_t damage, uint8_t range);

    Direccion getDirection();

    void release(float x_pos, float y_pos) override;
    void release(float x_pos, float y_pos, Direccion direction);
    void executeAction() override;
    ~CowBoyBullet() override;
};



#endif //BULLET_PISTOLA_COWBOY_H
