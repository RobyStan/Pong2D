//
// Created by Roby on 12/2/2023.
//

#include "Paddle.h"
#include "rlutil.h"

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

void Paddle::performAction(char key) {
    int screenHeight = rlutil::trows();

    if (key == 'm') {
        if (y > 0 && height + 2 <= screenHeight / 2) {
            y--;
            height += 2;
        }
    } else if (key == 'n') {
        if (height > 2) {
            y++;
            height -= 2;
        }
    }
}

GameObject *Paddle::clone() const {
    return new Paddle(*this);
}
