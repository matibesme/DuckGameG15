//
// Created by matibesme on 5/11/24.
//

#include "factory_weapons.h"

#include <cstdlib> // Para rand() y srand()
#include <ctime>   // Para time()

#include "ak47.h"
#include "banana.h"
#include "common_constant.h"
#include "cowboy_pistol.h"
#include "duel_pistol.h"
#include "granada.h"
#include "laser_rifle.h"
#include "magnum.h"
#include "pewpew_laser.h"
#include "server_constant.h"
#include "shotgun.h"
#include "sniper.h"

constexpr int TILE_CONSTANT = 6;

FactoryWeapons::FactoryWeapons() {}

std::shared_ptr<Weapon> FactoryWeapons::createWeapon(uint8_t type, float x,
                                                     float y) {
  switch (type) {
  case GRANADA_GUN:
    return std::make_shared<Granada>(GRANADA_GUN, UNO, x, y, DAMAGE_GRANADA,
                                     RANGE_GRANADA * TILE_CONSTANT,
                                     AMMO_GRANADA, RECOIL_GRANADA);
  case BANANA_GUN:
    return std::make_shared<Banana>(BANANA_GUN, UNO, x, y, DAMAGE_BANANA,
                                    RANGE_BANANA * TILE_CONSTANT, AMMO_BANANA,
                                    RECOIL_BANANA);
  case AK47_GUN:
    return std::make_shared<Ak47>(AK47_GUN, UNO, x, y, DAMAGE_AK47,
                                  RANGE_AK47 * TILE_CONSTANT, AMMO_AK47,
                                  RECOIL_AK47);
  case LASER_RIFLE_GUN:
    return std::make_shared<LaserRifle>(LASER_RIFLE_GUN, UNO, x, y,
                                        DAMAGE_LASER_RIFLE,
                                        RANGE_LASER_RIFLE * TILE_CONSTANT,
                                        AMMO_LASER_RIFLE, RECOIL_LASER_RIFLE);
  case PEW_PEW_LASER_GUN:
    return std::make_shared<PewPewLaser>(
        PEW_PEW_LASER_GUN, UNO, x, y, DAMAGE_PEW_PEW_LASER,
        RANGE_PEW_PEW_LASER * TILE_CONSTANT, AMMO_PEW_PEW_LASER,
        RECOIL_PEW_PEW_LASER);
  case ESCOPETA_GUN:
    return std::make_shared<Shotgun>(ESCOPETA_GUN, UNO, x, y, DAMAGE_ESCOPETA,
                                     RANGE_ESCOPETA * TILE_CONSTANT,
                                     AMMO_ESCOPETA, RECOIL_ESCOPETA);
  case SNIPER_GUN:
    return std::make_shared<Sniper>(SNIPER_GUN, UNO, x, y, DAMAGE_SNIPER,
                                    RANGE_SNIPER * TILE_CONSTANT, AMMO_SNIPER,
                                    RECOIL_SNIPER);
  case COWBOY_GUN:
    return std::make_shared<CowboyPistol>(COWBOY_GUN, UNO, x, y, DAMAGE_COWBOY,
                                          RANGE_COWBOY * TILE_CONSTANT,
                                          AMMO_COWBOY, RECOIL_COWBOY);
  case PISTOLA_DUELOS_GUN:
    return std::make_shared<DuelPistol>(
        PISTOLA_DUELOS_GUN, UNO, x, y, DAMAGE_PISTOLA_DUELOS,
        RANGE_PISTOLA_DUELOS * TILE_CONSTANT, AMMO_PISTOLA_DUELOS,
        RECOIL_PISTOLA_DUELOS);
  case MAGNUM_GUN:
    return std::make_shared<Magnum>(MAGNUM_GUN, UNO, x, y, DAMAGE_MAGNUM,
                                    RANGE_MAGNUM * TILE_CONSTANT, AMMO_MAGNUM,
                                    RECOIL_MAGNUM);

  default:
    return nullptr;
  }
}

std::shared_ptr<Weapon> FactoryWeapons::generateRandomWeapon(float pos_x,
                                                             float pos_y) {
  std::srand(std::time(nullptr));

  // Generar un número aleatorio correspondiente a los tipos de armas
  int random_number = std::rand() % DIEZ; // Hay 10 tipos de armas (0 a 9)

  switch (random_number) {
  case CERO:
    return createWeapon(GRANADA_GUN, pos_x, pos_y);
    break;
  case UNO:
    return createWeapon(BANANA_GUN, pos_x, pos_y);
    break;
  case DOS:
    return createWeapon(AK47_GUN, pos_x, pos_y);
    break;
  case TRES:
    return createWeapon(LASER_RIFLE_GUN, pos_x, pos_y);
    break;
  case CUATRO:
    return createWeapon(PEW_PEW_LASER_GUN, pos_x, pos_y);
    break;
  case CINCO:
    return createWeapon(ESCOPETA_GUN, pos_x, pos_y);
    break;
  case SEIS:
    return createWeapon(SNIPER_GUN, pos_x, pos_y);
    break;
  case SIETE:
    return createWeapon(COWBOY_GUN, pos_x, pos_y);
    break;
  case OCHO:
    return createWeapon(PISTOLA_DUELOS_GUN, pos_x, pos_y);
    break;
  case NUEVE:
    return createWeapon(MAGNUM_GUN, pos_x, pos_y);
    break;
  default:
    return nullptr;
    break;
  }
}
