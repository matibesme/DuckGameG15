//
// Created by ezequiel on 05/11/24.
//

#ifndef AK47_H
#define AK47_H
#include "weapon.h"
#include <vector>
#include <memory>


class Ak47 : public Weapon {
private:
  float spread_counter;
  std::vector<Bullet> bullets_vector;

public:
  Ak47(uint8_t type, uint8_t id, float x_pos, float y_pos, uint8_t damage,
       uint8_t range, int ammo_quantity, float recoil);

  bool isEmptyAmmo() override;

  std::unique_ptr<Bullet> shoot(bool is_aiming_up) override;

  bool isActive() override;

  void setReloadTime(int reload_time) override;

  int getReloadTime() override;

  void stopShooting() override;
};

#endif // AK47_H
