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

Border::~Border() {};

char Border::getSymbol() const {
    return '~';
}