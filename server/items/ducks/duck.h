#pragma once
#include <cstdint>
#include <list>
#include <memory>

#include "../common/common_constant.h"
#include "../objeto.h"
#include "../weapons/weapon.h"

class DuckPlayer : public Objeto {
private:
  bool is_weapon_equiped;
  uint8_t typeOfMove;
  bool saltando;
  float velocidad;
  uint8_t life;
  bool is_alive;
  float gravity;
  std::list<std::shared_ptr<Weapon>> weapons_list;
  uint8_t counter_flapping;
  bool is_flapping;
  uint8_t helmet;
  uint8_t armor;
  std::string color;
  bool is_aiming_up;

public:
  // Constructors
  DuckPlayer();
  DuckPlayer(uint8_t type, uint8_t id, float x_pos, float y_pos,
             std::string color_);

  // Getters
  uint8_t getTypeOfMoveSprite();
  Weapon &getWeapon();
  bool isWeaponEquipped();
  bool estaSaltando();
  bool isAlive();
  bool isFlapping();
  uint8_t &getHelmet();
  uint8_t &getArmor();
  bool receiveShoot();
  std::string &getColor();
  float &getVelocidadY();

  // Setters
  void setVelocidadY(float velocidad);
  void setTypeOfMoveSprite(uint8_t orientation);
  void setEnSalto(bool enSalto);
  void setFlapping(bool flapping);
  void setGravity(float gravity_);
  void setHelmet(uint8_t type);
  void setArmor(uint8_t type);

  // Actions
  void incrementXPos(float pos_x);
  void pickUpWeapon(std::shared_ptr<Weapon> weapon);
  void stopJump(float y_pos_);
  void executeAction();
  void applyDamage(uint8_t damage);
  void increaseFlappingCounter();
  std::shared_ptr<Weapon> removeWeapon();
  void aimUp();
  bool isAimingUp();
  void stopAimUp();

  // Destructor
  ~DuckPlayer();
};