#include "Game.h"
#include <algorithm>
#include <iostream>

int Game::paddleHits = 0;
int Game::borderHits = 0;

Game::~Game() {
    for (GameObject *obj : gameObjects) {
        delete obj;
    }
}

Game::Game(int width, int height, const Border &topAndBottomBorder)
        : screenWidth(width), screenHeight(height), topAndBottomBorder(topAndBottomBorder) {
    gameObjects.push_back(new Paddle(1, height / 2 - 3, 2, 6));
    gameObjects.push_back(new Paddle(width - 2, height / 2 - 3, 2, 6));
    gameObjects.push_back(new Ball(width / 2, height / 2, 1, 1));

    rlutil::hidecursor();
}

Game::Game(const Game &other)
        : screenWidth(other.screenWidth),
          screenHeight(other.screenHeight),
          topAndBottomBorder(other.topAndBottomBorder) {
    std::transform(
            other.gameObjects.begin(),
            other.gameObjects.end(),
            std::back_inserter(gameObjects),
            [](const GameObject *obj) { return obj->clone(); }
    );
}

Game& Game::operator=(const Game &other) {
    if (this != &other) {
        screenWidth = other.screenWidth;
        screenHeight = other.screenHeight;
        topAndBottomBorder = other.topAndBottomBorder;
        player1Score = other.player1Score;
        player2Score = other.player2Score;

        for (GameObject *obj : gameObjects) {
            delete obj;
        }
        gameObjects.clear();
                std::transform(
                other.gameObjects.begin(),
                other.gameObjects.end(),
                std::back_inserter(gameObjects),
                [](const GameObject *obj) { return obj->clone(); }
        );
    }
    return *this;
}

int Game::getPaddleHits() {
    return paddleHits;
}

int Game::getBorderHits() {
    return borderHits;
}

int Game::getTotalHits() {
    return paddleHits + borderHits;
}

void Game::handlePaddleCollisions(const Paddle &paddle, Ball &gameBall) {
    if (gameBall.getX() == paddle.getX() && gameBall.getY() >= paddle.getY() &&
        gameBall.getY() < paddle.getY() + paddle.getPaddleHeight()) {
        gameBall.reverseX();
        paddleHits++;
    }
}

void Game::resetGame() {
    for (GameObject *obj : gameObjects) {
        delete obj;
    }
    gameObjects.clear();
    gameObjects.push_back(new Paddle(1, screenHeight / 2 - 3, 2, 6));
    gameObjects.push_back(new Paddle(screenWidth - 2, screenHeight / 2 - 3, 2, 6));
    gameObjects.push_back(new Ball(screenWidth / 2, screenHeight / 2, 1, 1));
}

void Game::run() {
    try {
        resetGame();
        while (true) {
            if (kbhit()) {
                int key = std::tolower(rlutil::getkey());
                if (key == 'w') {
                    dynamic_cast<Paddle *>(gameObjects[0])->moveUp();
                }
                if (key == 's') {
                    dynamic_cast<Paddle *>(gameObjects[0])->moveDown(screenHeight);
                }
                if (key == 'i') {
                    dynamic_cast<Paddle *>(gameObjects[1])->moveUp();
                }
                if (key == 'j') {
                    dynamic_cast<Paddle *>(gameObjects[1])->moveDown(screenHeight);
                }
                if (key == 'q') {
                    throw GameOverException("User quit the game.\n");
                }
                if (key == '=') {
                    try {
                        dynamic_cast<Ball *>(gameObjects[2])->performAction('=');
                    } catch (const std::exception &ex) {
                        std::cerr << "Error performing action on Ball: " << ex.what() << std::endl;
                    }
                }
                if (key == '-') {
                    try {
                        dynamic_cast<Ball *>(gameObjects[2])->performAction('-');
                    } catch (const std::exception &ex) {
                        std::cerr << "Error performing action on Ball: " << ex.what() << std::endl;
                    }
                }
                if (key == 'm') {
                    dynamic_cast<Paddle *>(gameObjects[0])->performAction(key);
                    dynamic_cast<Paddle *>(gameObjects[1])->performAction(key);
                }
                if (key == 'n') {
                    dynamic_cast<Paddle *>(gameObjects[0])->performAction(key);
                    dynamic_cast<Paddle *>(gameObjects[1])->performAction(key);
                }
            }

            for (GameObject *obj : gameObjects) {
                obj->update();
            }

            if (dynamic_cast<Ball *>(gameObjects[2])->isWithin(0, screenHeight - 1)) {
                dynamic_cast<Ball *>(gameObjects[2])->reverseY();
                borderHits++;
            }

            for (const GameObject *obj : gameObjects) {
                if (const auto *paddle = dynamic_cast<const Paddle *>(obj)) {
                    handlePaddleCollisions(*paddle, *dynamic_cast<Ball *>(gameObjects[2]));
                }
            }

            if (dynamic_cast<Ball *>(gameObjects[2])->getX() < 0) {
                player2Score++;
                resetGame();
            } else if (dynamic_cast<Ball *>(gameObjects[2])->getX() >= screenWidth) {
                player1Score++;
                resetGame();
            }

            if (player1Score >= 5 || player2Score >= 5) {
                if (player1Score >= 5) {
                    std::cout << "Player 1 wins with a score of " << player1Score << "!\n" << std::endl;
                } else {
                    std::cout << "Player 2 wins with a score of " << player2Score << "!\n" << std::endl;
                }
                return;
            }
            render();
        }
    } catch (const std::exception &ex) {
        std::cerr << "Error in run: " << ex.what() << std::endl;
    }
}

void Game::renderBorder(int row) {
    for (int j = 0; j < screenWidth + 1; j++) {
        if (row == -1 || row == screenHeight) {
            std::cout << topAndBottomBorder.getSymbol();
        } else {
            renderGameElements(row, j);
        }
    }
    std::cout << std::endl;
}

void Game::renderGameElements(int row, int col) {
    if ((col == dynamic_cast<Paddle *>(gameObjects[0])->getX() ||
         col == dynamic_cast<Paddle *>(gameObjects[0])->getX() +
                dynamic_cast<Paddle *>(gameObjects[0])->getPaddleWidth() - 1) &&
        (row >= dynamic_cast<Paddle *>(gameObjects[0])->getY() &&
         row < dynamic_cast<Paddle *>(gameObjects[0])->getY() +
               dynamic_cast<Paddle *>(gameObjects[0])->getPaddleHeight())) {
        std::cout << dynamic_cast<Paddle *>(gameObjects[0])->getSymbol();
    } else if ((col == dynamic_cast<Paddle *>(gameObjects[1])->getX() ||
                col == dynamic_cast<Paddle *>(gameObjects[1])->getX() +
                       dynamic_cast<Paddle *>(gameObjects[1])->getPaddleWidth() - 1) &&
               (row >= dynamic_cast<Paddle *>(gameObjects[1])->getY() &&
                row < dynamic_cast<Paddle *>(gameObjects[1])->getY() +
                      dynamic_cast<Paddle *>(gameObjects[1])->getPaddleHeight())) {
        std::cout << dynamic_cast<Paddle *>(gameObjects[1])->getSymbol();
    } else if (col == dynamic_cast<Ball *>(gameObjects[2])->getX() &&
               row == dynamic_cast<Ball *>(gameObjects[2])->getY()) {
        std::cout << dynamic_cast<Ball *>(gameObjects[2])->getSymbol();
    } else {
        std::cout << " ";
    }
}

void Game::render() {
    rlutil::locate(1, 1);
    std::cout << "Player 1 Score: " << getPlayer1Score()
              << " | Player 2 Score: " << getPlayer2Score()
              << " | Paddle Hits: " << getPaddleHits()
              << " | Border Hits: " << getBorderHits()
              << " | Total Hits: " << getTotalHits() << std::endl;

    for (int i = -1; i <= screenHeight; i++) {
        renderBorder(i);
    }
}
