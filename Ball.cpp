//
// Created by Roby on 12/2/2023.
//

#include "GameExceptions.h"
#include "Ball.h"

Ball::Ball(int startX, int startY, double xSpeed, double ySpeed)
        : GameObject(startX, startY), xSpeed(xSpeed), ySpeed(ySpeed) {
    if (xSpeed <= 0 || ySpeed <= 0) {
        throw InvalidInputException("Invalid ball speed. Speed must be greater than zero.");
    }
}

Ball::Ball(const Ball &other)
        : GameObject(other), xSpeed(other.xSpeed), ySpeed(other.ySpeed) {}

Ball &Ball::operator=(const Ball &other)
{
    if (this != &other) {
        GameObject::operator=(other);
        xSpeed = other.xSpeed;
        ySpeed = other.ySpeed;
    }
    return *this;
}


Ball::~Ball() {}

void Ball::update()
{
    x = x + xSpeed;
    y = y + ySpeed;
}

void Ball::reverseX()
{
    xSpeed = -xSpeed;
}

void Ball::reverseY()
{
    ySpeed = -ySpeed;
}

bool Ball::isWithin(int minY, int maxY)
{
    return (y <= minY || y >= maxY);
}

char Ball::getSymbol() const {
    return 'O';
}

void Ball::performAction(char key) {
    if (key == '=') {
        xSpeed += 0.2;
        ySpeed += 0.2;
    }
    if (key == '-') {
        xSpeed -= 0.2;
        ySpeed -= 0.2;
    }
}

GameObject *Ball::clone() const {
    return new Ball(*this);
}

bool Ball::checkWallCollision(const MiddleWall &wall) const {
    return (x >= wall.getX() && x < wall.getX() + wall.getWidth()) &&
           (y >= wall.getY() && y < wall.getY() + wall.getHeight());
}

bool Ball::shouldDraw(int row, int col) const {
    return col == getX() && row == getY();
}

