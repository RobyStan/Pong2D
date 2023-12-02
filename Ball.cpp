//
// Created by Roby on 12/2/2023.
//

#include "Ball.h"

Ball::Ball(int startX, int startY)
        : x(startX), y(startY), xSpeed(1), ySpeed(1) {}

std::ostream& operator<<(std::ostream& os, const Ball& ball)
{
    os << "Ball position (x, y): (" << ball.x << ", " << ball.y << ")\n";
    os << "Ball speed(x_speed, y_speed): (" <<ball.xSpeed << ", " << ball.ySpeed << ")\n";
    return os;
}

int Ball::getX() const
{
    return x;
}
int Ball::getY() const
{
    return y;
}

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
    return (y < minY || y > maxY);
}
