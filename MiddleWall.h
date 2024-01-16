#ifndef OOP_MIDDLEWALL_H
#define OOP_MIDDLEWALL_H

#include "GameObject.h"

class MiddleWall : public GameObject {
private:
    int width, height;

public:
    MiddleWall(int startX, int startY, int width, int height);

    MiddleWall(const MiddleWall &other);

    MiddleWall &operator=(const MiddleWall &other);

    ~MiddleWall() override;

    char getSymbol() const override;

    void performAction(char) override;

    GameObject *clone() const override;

    int getWidth()const;

    int getHeight() const;
};

#endif //OOP_MIDDLEWALL_H
