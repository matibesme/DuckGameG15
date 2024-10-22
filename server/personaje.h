#include <cstdint>
#include "constant_definitons.h"
#include "element.h"

class Personaje: public Element {
    private:
        uint8_t typeOfMove;

    public:
        Personaje();
        void move(uint8_t movement);
        float getXPos();
        float getYPos();
        uint8_t getTypeOfMove();
        uint8_t getId();
        void setXPos(float pos_x, bool isRight);
        void setYPos(float pos_y, bool isJump);
        void setTypeOfMove(uint8_t orientation);
        void setId(uint8_t id);

        ~Personaje();

};