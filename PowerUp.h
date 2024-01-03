//
// Created by Roby on 1/3/2024.
//

#ifndef OOP_POWERUP_H
#define OOP_POWERUP_H

#include "GameObject.h"
#include "Ball.h"

class PowerUp : public GameObject {
private:

    double speedIncrement;

public:
    PowerUp(int startX, int startY, double speedIncrement);

    PowerUp(const PowerUp &other);

    PowerUp &operator=(const PowerUp &other);

    ~PowerUp() override;

    char getSymbol() const override;

    void performAction(char) override;

    GameObject *clone() const override;

};

#endif //OOP_POWERUP_H
