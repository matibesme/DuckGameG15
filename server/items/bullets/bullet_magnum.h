#ifndef BULLET_MAGNUM_H
#define BULLET_MAGNUM_H

#include "bullet.h"

class BulletMagnum : public Bullet {
public:
    BulletMagnum(uint8_t type, uint8_t id, float x_pos, float y_pos, uint8_t damage, uint8_t range, float spread);
    void executeAction() override;
    ~BulletMagnum() override;
};

#endif //BULLET_MAGNUM_H
