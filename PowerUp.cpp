//
// Created by Roby on 1/3/2024.
//

#include "PowerUp.h"
#include "Ball.h"

PowerUp::PowerUp(int startX, int startY, double speedIncrement)
        : GameObject(startX, startY), speedIncrement(speedIncrement) {}

PowerUp::PowerUp(const PowerUp &other)
        : GameObject(other), speedIncrement(other.speedIncrement) {}

PowerUp &PowerUp::operator=(const PowerUp &other) {
    if (this != &other) {
        GameObject::operator=(other);
        speedIncrement = other.speedIncrement;
    }
    return *this;
}

PowerUp::~PowerUp() {}

char PowerUp::getSymbol() const {
    return '+';
}

void PowerUp::performAction(char) {
    if (auto *ball = dynamic_cast<Ball *>(this)) {
        ball->performAction('+');
    }
}

GameObject *PowerUp::clone() const {
    return new PowerUp(*this);
}