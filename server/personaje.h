#include <cstdint>
#include "constant_definitons.h"
#include "objeto.h"

class Personaje: public Objeto {
    private:
        uint8_t typeOfMove;
        bool saltando;
        float velocidad;
    public:
        Personaje();
        void move(uint8_t movement);

        Personaje(uint8_t type, uint8_t id, float x_pos, float y_pos);

        float getXPos();
        float getYPos();
        uint8_t getTypeOfMoveSprite();
        uint8_t getId();
        void setXPos(float pos_x) override;

        void setTypeOfMoveSprite(uint8_t orientation);
        void setEnSalto(bool enSalto);
        bool estaSaltando();
        void setVelocidadY(float nueva_velocidad);
        float getVelocidadY();
        void executeAction();
        ~Personaje();

};