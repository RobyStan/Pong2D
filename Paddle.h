//
// Created by Roby on 12/2/2023.
//

#ifndef OOP_PADDLE_H
#define OOP_PADDLE_H

#include "iostream"


class Paddle
{
private:
    int x, y;
    int width, height;
public:
    Paddle(int startX, int startY, int paddleWidth, int paddleHeight);

    Paddle(const Paddle& other);

    Paddle& operator=(const Paddle& other);

    ~Paddle();

    friend std::ostream& operator<<(std::ostream& os, const Paddle& paddle);

    int getX() const;

    int getY() const;

    int getWidth() const;

    int getHeight() const;

    void moveUp();

    void moveDown(int screenHeight);
};

#endif //OOP_PADDLE_H
