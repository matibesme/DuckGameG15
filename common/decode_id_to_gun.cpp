#include "decode_id_to_gun.h"
#define BAZOOKA_ID 0x10
#define CHAINSAW_ID 0x11
#define DEATH_RAY_ID 0x12
#define SHOTGUN_ID 0x13
#define BAZOOKA "Bazooka"
#define CHAINSAW "Chainsaw"
#define DEATH_RAY "Death ray"
#define SHOTGUN "Shotgun"

DecodeIdToGun::DecodeIdToGun():
        id_to_gun({{BAZOOKA_ID, BAZOOKA},
                   {CHAINSAW_ID, CHAINSAW},
                   {DEATH_RAY_ID, DEATH_RAY},
                   {SHOTGUN_ID, SHOTGUN}}) {}

std::string DecodeIdToGun::get_gun(const uint8_t& id) { return id_to_gun[id]; }


DecodeIdToGun::~DecodeIdToGun() {}
