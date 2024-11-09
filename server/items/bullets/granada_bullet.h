//
// Created by matibesme on 29/10/24.
//

#ifndef GRANADA_BULLET_H
#define GRANADA_BULLET_H
#include "bullet.h"
#include "../common/common_constant.h"

class GranadaBullet : public Bullet {
private:
     uint8_t time_to_explode;
     float velocidad;
    bool continue_moving;
public:
    GranadaBullet(uint8_t type, uint8_t id, float x_pos, float y_pos, uint8_t damage, uint8_t range, float spread,uint8_t time_to_explode_);
    void executeAction() override;
    void release_granada(float x_pos, float y_pos, uint8_t direction,uint8_t time_to_explode);
    void setTimeToExplode(uint8_t time_to_explode_);
    void explode();
    void colisionWithPlatform(float plat_x_pos, float plat_y_pos, float plat_width, float plat_height) override;
};



#endif //GRANADA_BULLET_H
