//
// Created by Roby on 12/2/2023.
//

#ifndef OOP_BALL_H
#define OOP_BALL_H

#include "GameObject.h"
#include "MiddleWall.h"

class Ball : public GameObject
{
private:

    double xSpeed, ySpeed;

public:
    Ball(int startX, int startY, double xSpeed, double ySpeed);

    Ball(const Ball &other);

    Ball &operator=(const Ball &other);

    ~Ball() override;

    void update() override;

    void reverseX();

    void reverseY();

    bool isWithin(int minY, int maxY);

    char getSymbol() const override;

    void performAction(char key) override;

    GameObject *clone() const override;

    bool checkWallCollision(const MiddleWall &wall) const;
};

#endif //OOP_BALL_H
