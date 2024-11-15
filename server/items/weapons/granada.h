//
// Created by matibesme on 29/10/24.
//

#ifndef GRANADA_H
#define GRANADA_H
#include "../bullets/granada_bullet.h"
#include "weapon.h"

class Granada : public Weapon {
private:
  GranadaBullet bala;
  uint8_t counter_to_shoot;
  uint8_t time_to_explode;

public:
  Granada(uint8_t type, uint8_t id, float x_pos, float y_pos, uint8_t damage,
          uint8_t range, int ammo_quantity, float recoil);
  bool isEmptyAmmo() override;
  std::unique_ptr<Bullet> shoot(bool is_aiming_up) override;
  bool isActive() override;
  void setReloadTime(int reload_time) override;
  int getReloadTime() override;
  void stopShooting() override;
};

#endif // GRANADA_H
