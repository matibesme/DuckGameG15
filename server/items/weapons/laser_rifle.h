//
// Created by ezequiel on 05/11/24.
//
#ifndef LASER_RIFLE_H
#define LASER_RIFLE_H

#include "weapon.h"
#include <vector>

class LaserRifle : public Weapon {
private:
  float spread_counter;
  std::vector<Bullet> bullets_vector;

public:
  LaserRifle(uint8_t type, uint8_t id, float x_pos, float y_pos, int damage,
             uint8_t range, int ammo_quantity, float recoil);

  bool isEmptyAmmo() override;

  std::unique_ptr<Bullet> shoot(bool is_aiming_up) override;

  bool isActive() override;

  void setReloadTime(int reload_time) override;

  int getReloadTime() override;

  void stopShooting() override;
};

#endif // LASER_RIFLE_H
