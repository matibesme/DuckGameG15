//
// Created by matibesme on 30/10/24.
//

#ifndef BANANA_BULLET_H
#define BANANA_BULLET_H
#include "../common/common_constant.h"

#include "bullet.h"

class BananaBullet : public Bullet {
private:
  float velocidad;
  bool continue_moving;

public:
  BananaBullet(uint8_t type, uint8_t id, float x_pos, float y_pos,
               uint8_t damage, uint8_t range, float spread);
  void executeAction() override;
    void colisionWithPlatform(float plat_x_pos, float plat_y_pos,
                                float plat_width, float plat_height) override;
    bool colisionWithDuck(float duck_x_pos, float duck_y_pos, float duck_width, float duck_height) override;
};

#endif // BANANA_BULLET_H
