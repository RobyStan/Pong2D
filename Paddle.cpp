//
// Created by Roby on 12/2/2023.
//

#include "Paddle.h"

Paddle::Paddle(int startX, int startY, int paddleWidth, int paddleHeight)
        : GameObject(startX, startY), width(paddleWidth), height(paddleHeight) {}

Paddle::Paddle(const Paddle &other)
        : GameObject(other), width(other.width), height(other.height) {}

Paddle::~Paddle() {}

Paddle &Paddle::operator=(const Paddle &other) {
    if (this != &other) {
        GameObject::operator=(other);
        width = other.width;
        height = other.height;
    }
    return *this;
}

int Paddle::getPaddleWidth() const {
    return width;
}

int Paddle::getPaddleHeight() const {
    return height;
}

void Paddle::moveUp() {
    if (y > 0) {
        y--;
    }
}

void Paddle::moveDown(int screenHeight) {
    if (y + height < screenHeight) {
        y++;
    }
}

char Paddle::getSymbol() const {
    return '|';
}

void Paddle::performAction(char) {
    // do nothing
}

GameObject *Paddle::clone() const {
    return new Paddle(*this);
}
