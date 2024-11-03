#include "Box.h"
#include "common_constant.h"

#define IMAGE_BOX_WEAPON DATA_PATH "/objects/itemBox.png"
#define SPRITE_WIDTH_BOX 32
#define SPRITE_HEIGHT_BOX 32

Box::Box(uint8_t id, float initial_pos_x, float initial_pos_y, Graficos& graficos)
        : graficos(graficos), idBox(id),
          pos_x(initial_pos_x), pos_y(initial_pos_y),
          isDestroyed(false) {}

void Box::draw(SDL2pp::Renderer& renderer) {
    SDL2pp::Texture texture(graficos.LoadTexture(IMAGE_BOX_WEAPON));

    //arrea es el rectangulo que se toma de la textura
    SDL2pp::Rect area(0,0,SPRITE_WIDTH_BOX, SPRITE_HEIGHT_BOX);
    //destRect es el rectangulo donde se dibujara la textura
    SDL2pp::Rect destRect(pos_x, pos_y, WIDTH_BOX, HEIGHT_BOX);

    renderer.Copy(texture, area, destRect);
}

uint8_t Box::getId() {
    return idBox;
}
