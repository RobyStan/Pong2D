//
// Created by Roby on 12/27/2023.
//

#ifndef OOP_BORDER_H
#define OOP_BORDER_H

#include "GameObject.h"

class Border : public GameObject {
private:
    int screenWidth, screenHeight;

public:
    Border(int startX, int startY, int width, int height);

    Border(const Border &other);

    Border &operator=(const Border &other);

    ~Border() override;

    char getSymbol() const override;

    void performAction(char key) override;

    GameObject *clone() const override;

};

#endif //OOP_BORDER_H
