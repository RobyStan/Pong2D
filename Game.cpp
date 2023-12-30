#include "Game.h"

Game::Game(int width, int height, Border topAndBottomBorder)
        : screenWidth(width), screenHeight(height),
          player1(1, height / 2 - 3, 2, 6),
          player2(width - 2, height / 2 - 3, 2, 6),
          ball(width / 2, height / 2, 1, 1), topAndBottomBorder(topAndBottomBorder) {
    gameObjects.push_back(&player1);
    gameObjects.push_back(&player2);
    gameObjects.push_back(&ball);
    rlutil::hidecursor();
}


Game::~Game()
{
    for (GameObject *obj: gameObjects) {
        delete obj;
    }
}

void Game::handlePaddleCollisions(const Paddle &paddle, Ball &gameBall) {
    if (gameBall.getX() == paddle.getX() && gameBall.getY() >= paddle.getY() &&
        gameBall.getY() < paddle.getY() + paddle.getPaddleHeight()) {
        gameBall.reverseX();
    }
}

void Game::resetGame() {
    // Clear the gameObjects vector
    gameObjects.clear();

    // Create new objects and add them to the gameObjects vector
    ball = Ball(screenWidth / 2, screenHeight / 2, 1, 1);
    player1 = Paddle(1, screenHeight / 2 - 3, 2, 6);
    player2 = Paddle(screenWidth - 2, screenHeight / 2 - 3, 2, 6);

    gameObjects.push_back(&player1);
    gameObjects.push_back(&player2);
    gameObjects.push_back(&ball);
}

void Game::run() {
    resetGame();

    while (true) {
        if (kbhit()) {
            int key = std::tolower(rlutil::getkey());
            if (key == 'w') {
                player1.moveUp();
            }
            if (key == 's') {
                player1.moveDown(screenHeight);
            }
            if (key == 'i') {
                player2.moveUp();
            }
            if (key == 'j') {
                player2.moveDown(screenHeight);
            }
            if (key == 'q') {
                break;
            }
            if (key == '=') {
                ball.performAction(0.2);
            }
            if (key == '-') {
                ball.performAction(-0.2);
            }
        }

        for (GameObject *obj: gameObjects) {
            obj->update();
        }

        if (ball.getY() <= 0 || ball.getY() >= screenHeight - 1) {
            ball.reverseY();
        }

        for (const GameObject *obj: gameObjects) {
            if (const auto *paddle = dynamic_cast<const Paddle *>(obj)) {
                handlePaddleCollisions(*paddle, ball);
            }
        }

        if (ball.getX() < 0 || ball.getX() >= screenWidth) {
            resetGame();
        }

        render();
    }
}

void Game::renderBorder(int row) {
    for (int j = 0; j < screenWidth; j++) {
        if (row == -1 || row == screenHeight) {
            std::cout << topAndBottomBorder.getSymbol();
        } else {
            renderGameElements(row, j);
        }
    }
    std::cout << std::endl;
}

void Game::renderGameElements(int row, int col) {
    if ((col == player1.getX() || col == player1.getX() + player1.getPaddleWidth() - 1) &&
        (row >= player1.getY() && row < player1.getY() + player1.getPaddleHeight())) {
        std::cout << player1.getSymbol();
    } else if ((col == player2.getX() || col == player2.getX() + player2.getPaddleWidth() - 1) &&
               (row >= player2.getY() && row < player2.getY() + player2.getPaddleHeight())) {
        std::cout << player2.getSymbol();
    } else if (col == ball.getX() && row == ball.getY()) {
        std::cout << ball.getSymbol();
    } else {
        std::cout << " ";
    }
}

void Game::render() {
    rlutil::msleep(40);
    rlutil::locate(1, 1);

    for (int i = -1; i <= screenHeight; i++) {
        renderBorder(i);
    }
}