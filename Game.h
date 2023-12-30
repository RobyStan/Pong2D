// Game.h

#ifndef OOP_GAME_H
#define OOP_GAME_H

#include "Border.h"
#include "Paddle.h"
#include "Ball.h"
#include "GameObject.h"
#include "rlutil.h"
#include <vector>

class Game {
private:
    int screenWidth, screenHeight;
    Paddle player1, player2;
    Ball ball;
    Border topAndBottomBorder;
    std::vector<GameObject *> gameObjects;

public:
    Game(int width, int height, Border topAndBottomBorder);

    ~Game();

    void handlePaddleCollisions(const Paddle &paddle, Ball &gameBall);
    void resetGame();
    void run();
    void renderBorder(int row);
    void renderGameElements(int row, int col);
    void render();
};

#endif // OOP_GAME_H
