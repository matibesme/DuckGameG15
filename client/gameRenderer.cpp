#include "GameRenderer.h"

GameRenderer::GameRenderer(Graficos& graficos)
        : graficos(graficos), background(graficos) {}

void GameRenderer::dibujar(Renderer& renderer, std::list<ClientDuck>& ducks, std::list<Bullet>& bullets) {
    renderer.Clear();
    background.draw(renderer);

    for (auto& duck : ducks) {
        duck.draw(renderer);
    }
    for (auto& bullet : bullets) {
        bullet.draw(renderer);
    }

    renderer.Present();
}
