//
// Created by Roby on 12/26/2023.
//

#include "GameObject.h"

GameObject::GameObject(int startX, int startY) : x(startX), y(startY) {}

GameObject::GameObject(const GameObject &gameObject)
        : x(gameObject.x), y(gameObject.y) {}

GameObject &GameObject::operator=(const GameObject &gameObject) {
    if (this != &gameObject) {
        x = gameObject.x;
        y = gameObject.y;
    }
    return *this;
}

GameObject::~GameObject() {}

int GameObject::getX() const {
    return x;
}

int GameObject::getY() const {
    return y;
}

void GameObject::update() {
    // do nothing
}

int GameObject::getWidth() {
    return 1;
}

int GameObject::getHeight() {
    return 6;
}

void GameObject::performAction() {
    // Default implementation, do nothing
}
