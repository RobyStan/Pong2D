//
// Created by Roby on 12/26/2023.
//

#ifndef OOP_GAMEOBJECT_H
#define OOP_GAMEOBJECT_H

class GameObject {
protected:
    int x, y;

public:
    GameObject(int startX, int startY);

    virtual ~GameObject();

    GameObject(const GameObject &gameObject);

    GameObject &operator=(const GameObject &gameObject);

    virtual char getSymbol() const = 0;

    virtual void update();

    virtual int getX() const;

    virtual int getY() const;

    virtual void performAction() = 0;

};

#endif //OOP_GAMEOBJECT_H
