#ifndef BUlLET_DUEL_PISTOL_H
#define BUlLET_DUEL_PISTOL_H

#include "bullet.h"

class BulletDuelPistol : public Bullet {

public:
    BulletDuelPistol(uint8_t type, uint8_t id, float x_pos, float y_pos, uint8_t damage, uint8_t range, float spread);
    void executeAction() override;
    ~BulletDuelPistol() override;
};


#endif //BUlLET_DUEL_PISTOL_H
