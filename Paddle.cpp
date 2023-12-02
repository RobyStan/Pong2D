//
// Created by Roby on 12/2/2023.
//

#include "Paddle.h"

Paddle::Paddle(int startX, int startY, int paddleWidth, int paddleHeight):
        x(startX), y(startY),
        width(paddleWidth), height(paddleHeight) {}

Paddle::Paddle(const Paddle& other) : x(other.x), y(other.y), width(other.width), height(other.height) {}

Paddle::~Paddle() {}

Paddle &Paddle::operator=(const Paddle& other)
{
    this->x = other.x;
    this->y = other.y;
    this->width = other.width;
    this->height = other.height;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Paddle& paddle)
{
    os << "Paddle position (x, y): (" << paddle.x << ", " << paddle.y << ")\n";
    os << "Paddle dimensions (width, height): (" << paddle.width << ", " << paddle.height << ")\n";
    return os;
}

int Paddle::getX() const
{
    return x;
}

int Paddle::getY() const
{
    return y;
}

int Paddle::getWidth() const
{
    return width;
}

int Paddle::getHeight() const
{
    return height;
}

void Paddle::moveUp()
{
    if (y > 0)
    {
        y--;
    }
}

void Paddle::moveDown(int screenHeight)
{
    if (y + height < screenHeight)
    {
        y++;
    }
}





