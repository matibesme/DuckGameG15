#pragma once
#include "../common/common_constant.h"
#include "../objeto.h"
#include "../weapons/weapon.h"
#include <cstdint>
#include <list>
#include <memory>
#include <string>

class DuckPlayer : public Objeto {
private:
  bool is_weapon_equiped;
  uint8_t typeOfMove;
  bool saltando;
  float velocidad;
  int life;
  bool is_alive;
  float gravity;
  std::list<std::shared_ptr<Weapon>> weapons_list;
  int counter_flapping;
  bool is_flapping;
  uint8_t helmet;
  uint8_t armor;
  std::string color;
  bool is_aiming_up;
  bool is_sliding;
  int slide_counter;
  int respond_after_sliding;

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
  int getRespondAfterSliding();

  // Setters
  void setVelocidadY(float velocidad);
  void setTypeOfMoveSprite(uint8_t orientation);
  void setEnSalto(bool enSalto);
  void setFlapping(bool flapping);
  void setColor(std::string &color_);
  void setGravity(float gravity_);
  void setHelmet(uint8_t type);
  void setArmor(uint8_t type);
  void setIsSliding(bool sliding);
  void setRespondAfterSliding(int respond_after_sliding_);

  // Actions
  void incrementXPos(float pos_x);
  void pickUpWeapon(std::shared_ptr<Weapon> weapon);
  void stopJump(float y_pos_);
  void executeAction(std::string &color_);
  void applyDamage(int damage);
  void increaseFlappingCounter();
  std::shared_ptr<Weapon> removeWeapon();
  void aimUp();
  bool isAimingUp();
  void stopAimUp();
  void eraseGun();
  bool isSliding();
  uint8_t checkSlideColision();

  // Destructor
  ~DuckPlayer();
};
