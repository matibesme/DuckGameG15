

class Personaje{
    private:
        uint16_t x_pos;
        uint16_t y_pos;
        uint8_t orientation;

    public:
        Personaje(uint16_t x_pos, uint16_t y_pos, uint8_t orientation);
        void move(uint8_t movement);
        uint16_t getXPos();
        uint16_t getYPos();
        uint8_t getOrientation();
        void setXPos(uint16_t x_pos);
        void setYPos(uint16_t y_pos);
        void setOrientation(uint8_t orientation);
        ~Personaje();

}