#include <cstdint>
#include "../../constant_definitons.h"
#include "../objeto.h"
#include "../weapons/weapon.h"

class DuckPlayer: public Objeto {
    private:
        bool is_weapon_equiped;
        uint8_t typeOfMove;
        bool saltando;
        float velocidad;
        Weapon weapon;
        std::list<Weapon> weapons_list;
    public:

        //constructor por defecto
        DuckPlayer(): Objeto(0,0,0,0), is_weapon_equiped(false), typeOfMove(S_STILL_RIGTH), saltando(false), velocidad(VELOCIDAD_INICIAL), weapon(S_COWBOY_GUN, 1, 0, 0, 5, 20, 10,3){}

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
        ~DuckPlayer();

};