//
// Created by Roby on 12/2/2023.
//

#include "Paddle.h"
#include "rlutil.h"

Paddle::Paddle(int startX, int startY, int paddleWidth, int paddleHeight, char player)
        : GameObject(startX, startY), width(paddleWidth), height(paddleHeight), player(player) {}

Paddle::Paddle(const Paddle &other)
        : GameObject(other), width(other.width), height(other.height), player(other.player) {}

Paddle::~Paddle() {}

Paddle &Paddle::operator=(const Paddle &other) {
    if (this != &other) {
        GameObject::operator=(other);
        width = other.width;
        height = other.height;
        player = other.player;
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
    if (player == '1') {
        if (key == 'w') {
            moveUp();
        }
        if (key == 's') {
            moveDown(rlutil::trows());
        }
    } else if (player == '2') {
        if (key == 'i') {
            moveUp();
        }
        if (key == 'j') {
            moveDown(rlutil::trows());
        }
    }
}

GameObject *Paddle::clone() const {
    return new Paddle(*this);
}
