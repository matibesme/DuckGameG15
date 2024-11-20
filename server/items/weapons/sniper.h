//
// Created by ezequiel on 31/10/24.
//

#ifndef SNIPER_H
#define SNIPER_H
#include "weapon.h"
#include <memory>

class Sniper : public Weapon {
private:
  Bullet bala;

public:
  Sniper(uint8_t type, uint8_t id, float x_pos, float y_pos, int damage,
         int range, int ammo_quantity, float recoil);

  bool isEmptyAmmo() override;

  std::unique_ptr<Bullet> shoot(bool is_aiming_up) override;

  bool isActive() override;

  void setReloadTime(int reload_time) override;
  int getReloadTime() override;
  void stopShooting() override;
};

#endif // SNIPER_H
