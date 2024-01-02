//
// Created by Roby on 12/2/2023.
//

#ifndef OOP_PADDLE_H
#define OOP_PADDLE_H

#include "GameObject.h"

class Paddle : public GameObject
{
private:
    int width, height;

public:
    Paddle(int startX, int startY, int paddleWidth, int paddleHeight);

    Paddle(const Paddle& other);

    Paddle& operator=(const Paddle& other);

    ~Paddle() override;

    int getPaddleWidth() const;

    int getPaddleHeight() const;

    void moveUp();

    void moveDown(int screenHeight);

    char getSymbol() const override;

    void performAction(char) override;

    GameObject *clone() const override;

};

#endif //OOP_PADDLE_H
