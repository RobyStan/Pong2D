//
// Created by Roby on 12/27/2023.
//

#include "Border.h"

Border::Border(int startX, int startY, int width, int height)
        : GameObject(startX, startY), screenWidth(width), screenHeight(height) {}

Border::Border(const Border &other)
        : GameObject(other), screenWidth(other.screenWidth), screenHeight(other.screenHeight) {}

Border &Border::operator=(const Border &other) {
    if (this != &other) {
        GameObject::operator=(other);
        screenWidth = other.screenWidth;
        screenHeight = other.screenHeight;
    }
    return *this;
}

Border::~Border() {}

char Border::getSymbol() const {
    return '~';
}

void Border::performAction(char) {
    // do nothing
}

GameObject *Border::clone() const {
    return new Border(*this);
}

bool Border::shouldDraw(int row, int col) const {
    return (row == -1 || row == screenHeight);
}
