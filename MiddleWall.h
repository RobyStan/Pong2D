#ifndef OOP_MIDDLEWALL_H
#define OOP_MIDDLEWALL_H

#include "GameObject.h"

class MiddleWall : public GameObject {
private:
    int width, height;
    int direction;

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

    char updatePosition(char key);

    bool shouldDraw(int row, int col) const override;

};

#endif //OOP_MIDDLEWALL_H