#include <cstdint>
#include "constant_definitons.h"
#include "objeto.h"

class Personaje: public Objeto {
    private:
        uint8_t typeOfMove;
        bool saltando;

    public:
        Personaje();
        void move(uint8_t movement);
        float getXPos();
        float getYPos();
        uint8_t getTypeOfMoveSprite();
        uint8_t getId();
        void setXPos(float pos_x);
        void setYPos(float pos_y);
        void setTypeOfMoveSprite(uint8_t orientation);

        void setEnSalto(bool enSalto);
        bool estaSaltando();
        ~Personaje();

};