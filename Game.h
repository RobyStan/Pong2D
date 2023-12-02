//
// Created by Roby on 12/2/2023.
//

#ifndef OOP_GAME_H
#define OOP_GAME_H

#include "Paddle.h"
#include "Ball.h"
#include "iostream"
#include "rlutil.h"

class Game
{
private:
    int screenWidth, screenHeight;
    Paddle player1, player2;
    Ball ball;
public:
    Game(int width, int height);

    friend std::ostream &operator<<(std::ostream &os, const Game &pingPongGame);

    void handlePaddleCollisions(const Paddle &paddle, const Ball &gameBall);

    void resetGame();

    void run();

    void renderBorder(int row);

    void renderGameElements(int row, int col);

    void render();
};


#endif //OOP_GAME_H
