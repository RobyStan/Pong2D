#include "Game.h"
#include <algorithm>
#include <iostream>
#include <chrono>

int Game::paddleHits = 0;
int Game::borderHits = 0;

Game::~Game() {
    for (GameObject *obj : gameObjects) {
        delete obj;
    }
}

Game::Game(int width, int height, const Border &topAndBottomBorder)
        : screenWidth(width), screenHeight(height), topAndBottomBorder(topAndBottomBorder) {
    gameObjects.push_back(new Paddle(1, height / 2 - 3, 2, 6, '1'));
    gameObjects.push_back(new Paddle(width - 2, height / 2 - 3, 2, 6, '2'));
    gameObjects.push_back(new Ball(width / 2, height / 2, 1, 1));
    gameObjects.push_back(new MiddleWall(screenWidth / 2, screenHeight / 2 - 9, 2, screenHeight/5));
    gameObjects.push_back(new MiddleWall(screenWidth / 2, screenHeight / 2 + 6,2,screenHeight/5));

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

// cppcheck-suppress operatorEqRetRefThis
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

void Game::handleCollisions(const Paddle &paddle, Ball &gameBall) {
    if (gameBall.getX() == paddle.getX() && gameBall.getY() >= paddle.getY() &&
        gameBall.getY() < paddle.getY() + paddle.getPaddleHeight()) {
        gameBall.reverseX();
        paddleHits++;
    } else {
        for (const GameObject *obj : gameObjects) {
            if (const auto *middleWall = dynamic_cast<const MiddleWall *>(obj)) {
                if (gameBall.checkWallCollision(*middleWall)) {
                    gameBall.reverseX();
                }
            }
        }
    }
}

void Game::resetGame() {
    for (GameObject *obj: gameObjects) {
        delete obj;
    }
    gameObjects.clear();
    gameObjects.push_back(new Paddle(1, screenHeight / 2 - 3, 2, 6, '1'));
    gameObjects.push_back(new Paddle(screenWidth - 2, screenHeight / 2 - 3, 2, 6, '2'));
    gameObjects.push_back(new Ball(screenWidth / 2, screenHeight / 2, 1, 1));
    gameObjects.push_back(new MiddleWall(screenWidth / 2, screenHeight / 2 - 9, 2, screenHeight / 5));
    gameObjects.push_back(new MiddleWall(screenWidth / 2, screenHeight / 2 + 6, 2, screenHeight / 5));
}

void Game::run() {
    try {
        resetGame();

        //  auto lastWallMoveTime = std::chrono::high_resolution_clock::now();

        while (true) {
            if (kbhit()) {
                int key = std::tolower(rlutil::getkey());
                for (auto obj: gameObjects) {
                    obj->performAction(key);
                }
                if (key == 'q') {
                    throw GameOverException("User quit the game.\n");
                }
            }

            for (auto obj: gameObjects) {
                obj->update();
            }

            auto ball = dynamic_cast<Ball *>(gameObjects[2]);
            if (ball && ball->isWithin(0, screenHeight - 1)) {
                ball->reverseY();
                borderHits++;
            }

            for (auto obj: gameObjects) {
                if (auto *paddle = dynamic_cast<const Paddle *>(obj)) {
                    handleCollisions(*paddle, *ball);
                }
                }

//                auto currentTime = std::chrono::high_resolution_clock::now();
//                auto wallElapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - lastWallMoveTime).count();
//
//                for (auto obj : gameObjects) {
//                    if (auto middleWall = dynamic_cast<MiddleWall*>(obj)) {
//                        middleWall->updatePosition('m');
//                    }
//                }
//                        if (wallElapsedTime >= 2) {
//                    for (auto obj : gameObjects) {
//                        if (auto middleWall = dynamic_cast<MiddleWall*>(obj)) {
//                            middleWall->performAction(middleWall->updatePosition('m'));
//                            middleWall->updatePosition();
//                        }
//                    }
//
//                    lastWallMoveTime = std::chrono::high_resolution_clock::now();
//                }

//  Peretii din mijloc se vor misca singur in sus si in jos 1 singur spatiu la un interval de 2 secunde

            if (ball->getX() < 0) {
                player2Score++;
                resetGame();
            } else if (ball->getX() >= screenWidth) {
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
    auto it = std::find_if(gameObjects.begin(), gameObjects.end(),
                           [&](const GameObject *obj) { return obj->shouldDraw(row, col); });

    if (it != gameObjects.end()) {
        std::cout << (*it)->getSymbol();
        return;
    }

    std::cout << " ";
}

void Game::render() {
    rlutil::msleep(40);
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
