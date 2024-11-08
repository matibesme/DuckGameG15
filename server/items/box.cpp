//
// Created by ezequiel on 07/11/24.
//
/*
#include "box.h"



Box::Box(uint8_t type, uint8_t id, float x_pos, float y_pos, int health) :
        Objeto(type, id, x_pos, y_pos),
        health(health),
        content(std::monostate()) {
    generateRandomContent();
}

void Box::generateRandomContent() {
    // Semilla para el generador de números aleatorios
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 4);

    int random_choice = dist(gen);
    switch (random_choice) {
        case 1:
            content = std::make_unique<Weapon>(/);
        break;
        case 2:
            content = std::make_unique<Armor>();
        break;
        case 3:
            content = std::make_unique<Helmet>();
        break;
        case 4:
            content = std::make_unique<Explosive>();
        break;
        default:
            content = std::monostate(); // Caja vacía
        break;
    }
}

void Box::takeDamage(int damage) {
    health -= damage;
}

bool Box::isDestroyed() const {
    return health <= 0;
}

std::variant<std::monostate, std::unique_ptr<Weapon>, std::unique_ptr<Armor>,
                 std::unique_ptr<Helmet>, std::unique_ptr<Explosive>>& Box::getContent() {
    if (isDestroyed()) {
        return content;
    } else {
        return std::monostate(); // Si la caja no está destruida, no tiene contenido accesible
    }
}

*/
