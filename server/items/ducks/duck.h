#pragma once
#include <cstdint>
#include "../common/common_constant.h"
#include "../objeto.h"
#include "../weapons/weapon.h"
#include <list>
#include <memory>

class DuckPlayer: public Objeto {
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

    public:
        DuckPlayer();
        DuckPlayer(uint8_t type, uint8_t id, float x_pos, float y_pos);

        uint8_t getTypeOfMoveSprite();
        void incrementXPos(float pos_x) ;
        Weapon& getWeapon();
        void pickUpWeapon(std::shared_ptr<Weapon> weapon);

        bool isWeaponEquipped();
        void setVelocidadY(float velocidad);

        void setTypeOfMoveSprite(uint8_t orientation);
        void setEnSalto(bool enSalto);
        bool estaSaltando();

        float& getVelocidadY();
        void stopJump(float y_pos_);
        void executeAction();

        bool isAlive();
        void applyDamage(uint8_t damage);
        void setFlapping(bool flapping);
        bool isFlapping();
        void setGravity(float gravity_);
        void increaseFlappingCounter();

        //void setWeapon(Weapon& weapon);
        void removeWeapon();
        ~DuckPlayer();

};