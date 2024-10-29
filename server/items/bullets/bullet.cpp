#include "bullet.h"
#include <random>

Bullet::Bullet(uint8_t type, uint8_t id, float x_pos, float y_pos, uint8_t damage, uint8_t range, float spread):
    Objeto(type, id, x_pos, y_pos),
    damage(damage),
    range(range),
    is_alive(true),
    spread(spread),
    spread_direction(false) {}


uint8_t Bullet::getDamage() {
    return damage;
}

uint8_t Bullet::getRange() {
    return range;
}

bool Bullet::isAlive() {
    return this->is_alive;
}

uint8_t Bullet::getTypeOfBullet() {
    return type;
}

void Bullet::release(float x_pos, float y_pos, uint8_t direction) {
    this->x_pos = x_pos;
    this->y_pos = y_pos;
    this->direction = direction;
    randomSpread() ? spread_direction = true : spread_direction = false;
}

bool randomSpread() {
    // Inicializa el generador de números aleatorios con un "motor" de generación aleatoria
    std::random_device rd;  // fuente de entropía no determinista
    std::mt19937 gen(rd()); // motor generador de números aleatorios basado en Mersenne Twister

    // Distribución uniforme entre 0 y 1 para representar "falso" y "verdadero"
    std::bernoulli_distribution dist(0.5); // probabilidad de 50% para cada valor

    return dist(gen); // genera un valor verdadero o falso
}

void Bullet::executeAction(){
    if (is_alive && range > 0) {
        if (direction == S_RIGTH) {
            x_pos += BULLET_VEL;
            spread_direction ? y_pos += spread : y_pos -= spread;
        } else if (direction == S_LEFT) {
            x_pos -= BULLET_VEL;
            spread_direction ? y_pos += spread : y_pos -= spread;
        } else if (direction == S_UP) {
            y_pos -= BULLET_VEL;
            spread_direction ? x_pos += spread : x_pos -= spread;
        }
        range--;
        if (range == 0) {
            is_alive = false;
        }
    }
}

void Bullet::kill() {
    is_alive = false;
}
