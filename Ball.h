//
// Created by Roby on 12/2/2023.
//

#ifndef OOP_BALL_H
#define OOP_BALL_H

#include "iostream"

class Ball
{
private:
    double x, y;
    double xSpeed, ySpeed;
public:
    Ball(int startX, int startY);

    int getX() const;

    int getY() const;

    void update();

    void reverseX();

    void reverseY();

    bool isWithin(int minY, int maxY);

    friend std::ostream& operator<<(std::ostream& os, const Ball& ball);
};


#endif //OOP_BALL_H
