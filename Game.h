#ifndef OOP_GAME_H
#define OOP_GAME_H

#include "Border.h"
#include "Paddle.h"
#include "Ball.h"
#include "GameObject.h"
#include "rlutil.h"
#include <vector>
#include "GameExceptions.h"
#include "MiddleWall.h"

class Game {
private:
    int screenWidth, screenHeight;
    int player1Score{}, player2Score{};
    Border topAndBottomBorder;
    std::vector<GameObject *> gameObjects;
    static int paddleHits;
    static int borderHits;

public:
    Game(int width, int height, const Border &topAndBottomBorder);

    ~Game();

    Game(const Game &other);

    Game &operator=(const Game &other);

    int getPlayer1Score() const { return player1Score; }

    int getPlayer2Score() const { return player2Score; }

    void handleCollisions(const Paddle &paddle, Ball &gameBall);
    void resetGame();
    void run();
    void renderBorder(int row);
    void renderGameElements(int row, int col);
    void render();

    static int getPaddleHits();

    static int getBorderHits();

    static int getTotalHits();
};

#endif // OOP_GAME_H