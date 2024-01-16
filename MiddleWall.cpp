#include "MiddleWall.h"

MiddleWall::MiddleWall(int startX, int startY, int width, int height)
        : GameObject(startX, startY), width(width), height(height) {}

MiddleWall::MiddleWall(const MiddleWall &other)
        : GameObject(other), width(other.width), height(other.height) {}

MiddleWall &MiddleWall::operator=(const MiddleWall &other) {
    if (this != &other) {
        GameObject::operator=(other);
        width = other.width;
        height = other.height;
    }
    return *this;
}
MiddleWall::~MiddleWall() {}

char MiddleWall::getSymbol() const {
    return '#';
}

void MiddleWall::performAction(char) {
   // do nothing for now
}

GameObject *MiddleWall::clone() const {
    return new MiddleWall(*this);
}

int MiddleWall::getWidth() const {
    return width;
}

int MiddleWall::getHeight() const {
    return height;
}
