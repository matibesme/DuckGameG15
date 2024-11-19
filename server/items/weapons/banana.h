//
// Created by matibesme on 30/10/24.
//

#ifndef BANANA_H
#define BANANA_H
#include "../bullets/banana_bullet.h"
#include "weapon.h"

class Banana : public Weapon {
private:
  BananaBullet bala;
  uint8_t counter_to_shoot;
  uint8_t time_to_explode;

public:
  Banana(uint8_t type, uint8_t id, float x_pos, float y_pos, int damage,
         uint8_t range, int ammo_quantity, float recoil);
  bool isEmptyAmmo() override;
  bool isActive() override;
  std::unique_ptr<Bullet> shoot(bool is_aiming_up) override;
  void setReloadTime(int reload_time) override;
  int getReloadTime() override;
  void stopShooting() override;
};

#endif // BANANA_H
