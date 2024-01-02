// Game.h

#ifndef OOP_GAME_H
#define OOP_GAME_H

#include "Border.h"
#include "Paddle.h"
#include "Ball.h"
#include "GameObject.h"
#include "rlutil.h"
#include <vector>
#include "GameExceptions.h"


class Game {
private:
    int screenWidth, screenHeight;
    int player1Score{}, player2Score{};
    Paddle player1, player2;
    Ball ball;
    Border topAndBottomBorder;
    std::vector<GameObject *> gameObjects;

public:
    Game(int width, int height, const Border &topAndBottomBorder);

    ~Game();

    Game(const Game &other);

    Game &operator=(Game &other);

    int getPlayer1Score() const { return player1Score; }

    int getPlayer2Score() const { return player2Score; }

    static void handlePaddleCollisions(const Paddle &paddle, Ball &gameBall);
    void resetGame();
    void run();
    void renderBorder(int row);
    void renderGameElements(int row, int col);
    void render();
};

#endif // OOP_GAME_H
