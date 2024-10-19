#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2pp/SDL2pp.hh>

using namespace SDL2pp;

class Duck {
public:
    Duck(float initialX, float initialY);
    void update(bool moveRight, bool moveLeft, unsigned int frameDelta);
    void draw(SDL2pp::Renderer& renderer, SDL2pp::Texture& sprites);
    void setOnFloor(bool onFloor);
    float getPosition() const;

private:
    float positionX;
    int runPhase;
    bool isMovingRight;
    bool isMovingLeft;
    bool isOnFloor;
};

#endif // PLAYER_H
