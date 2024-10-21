

class Personaje{
    private:
        uint8_t type;
        uint8_t id;
        uint16_t x_pos;
        uint16_t y_pos;
        uint8_t orientation;

    public:
        Personaje(uint16_t x_pos, uint16_t y_pos, uint8_t orientation);
        void move(uint8_t movement);
        uint16_t getXPos();
        uint16_t getYPos();
        uint8_t getOrientation();
        uint8_t getId();
        void setXPos(uint16_t x_pos, bool isRight);
        void setYPos(uint16_t y_pos, bool isJump);
        void setOrientation(uint8_t orientation);
        void setId(uint8_t id);

        ~Personaje();

}