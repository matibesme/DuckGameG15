#include <cstdint>


class Personaje{
    private:
        uint8_t type;
        uint8_t id;
        float x_pos;
        float y_pos;
        uint8_t orientation;

    public:
        Personaje();
        void move(uint8_t movement);
        float getXPos();
        float getYPos();
        uint8_t getOrientation();
        uint8_t getId();
        void setXPos(float x_pos, bool isRight);
        void setYPos(float y_pos, bool isJump);
        void setOrientation(uint8_t orientation);
        void setId(uint8_t id);

        ~Personaje();

};