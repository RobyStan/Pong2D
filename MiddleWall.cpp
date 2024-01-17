#include "MiddleWall.h"
#include "rlutil.h"

MiddleWall::MiddleWall(int startX, int startY, int width, int height)
        : GameObject(startX, startY), width(width), height(height), direction(1) {}

MiddleWall::MiddleWall(const MiddleWall &other)
        : GameObject(other), width(other.width), height(other.height), direction(other.direction) {}

MiddleWall &MiddleWall::operator=(const MiddleWall &other) {
    if (this != &other) {
        GameObject::operator=(other);
        width = other.width;
        height = other.height;
        direction = other.direction;
    }
    return *this;
}

MiddleWall::~MiddleWall() {}


char MiddleWall::getSymbol() const {
    return '#';
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

void MiddleWall::performAction(char key) {

    if (key == 'm') {
        y--;
    }
    if (key == 'n') {
        y++;
    }
}

//char MiddleWall::updatePosition(char key) {
//    if (key == 'm') {
//        return 'n';
//    } else if (key == 'n') {
//        return 'm';
//    }
//}