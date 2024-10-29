#include <cstdint>
#include "../../constant_definitons.h"
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
        std::list<std::shared_ptr<Weapon>> weapons_list;
    public:

        //constructor por defecto
        DuckPlayer(): Objeto(0,0,0,0),
        is_weapon_equiped(false),
        typeOfMove(S_STILL_RIGTH),
        saltando(false),
        velocidad(VELOCIDAD_INICIAL){}
        DuckPlayer(): Objeto(0,0,0,0), is_weapon_equiped(false), typeOfMove(S_STILL_RIGTH), saltando(false), velocidad(VELOCIDAD_INICIAL), life(100), is_alive(true),gravity(GRAVEDAD),
        weapon(S_COWBOY_GUN, 1, 0, 0, 5, 20, 10,3){}


        DuckPlayer(uint8_t type, uint8_t id, float x_pos, float y_pos);


        uint8_t getTypeOfMoveSprite();
        void incrementXPos(float pos_x) ;
        Weapon& getWeapon();

        void equippWeapon();
        void unequippWeapon();
        void setVelocidadY(float velocidad);

        void setTypeOfMoveSprite(uint8_t orientation);
        void setEnSalto(bool enSalto);
        bool estaSaltando();

        float& getVelocidadY();
        void executeAction();

        bool isAlive();
        void applyDamage(uint8_t damage);
        void setFlapping(bool flapping);
        void setGravity(float gravity_);
        void increaseFlappingCounter();
        ~DuckPlayer();

};