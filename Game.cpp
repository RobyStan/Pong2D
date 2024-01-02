#include "Game.h"
#include <algorithm>

Game::Game(int width, int height, const Border &topAndBottomBorder)
        : screenWidth(width), screenHeight(height),
          player1(1, height / 2 - 3, 2, 6),
          player2(width - 2, height / 2 - 3, 2, 6),
          ball(width / 2, height / 2, 1, 1), topAndBottomBorder(topAndBottomBorder) {
    gameObjects.push_back(&player1);
    gameObjects.push_back(&player2);
    gameObjects.push_back(&ball);
    rlutil::hidecursor();
}

Game::Game(const Game &other)
        : screenWidth(other.screenWidth),
          screenHeight(other.screenHeight),
          player1Score(other.player1Score),
          player2Score(other.player2Score),
          player1(other.player1),
          player2(other.player2),
          ball(other.ball),
          topAndBottomBorder(other.topAndBottomBorder) {
    for (const GameObject *obj: other.gameObjects) {
        std::transform(
                other.gameObjects.begin(),
                other.gameObjects.end(),
                std::back_inserter(gameObjects),
                [](const GameObject *obj) { return obj->clone(); }
        );
    }
}

Game &Game::operator=(Game &other) {
    std::swap(screenWidth, other.screenWidth);
    std::swap(screenHeight, other.screenHeight);
    std::swap(player1, other.player1);
    std::swap(player2, other.player2);
    std::swap(ball, other.ball);
    std::swap(topAndBottomBorder, other.topAndBottomBorder);
    std::swap(player1Score, other.player1Score);
    std::swap(player2Score, other.player2Score);
    std::swap(gameObjects, other.gameObjects);

    return *this;
}

Game::~Game() {
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
    gameObjects.clear();

    ball = Ball(screenWidth / 2, screenHeight / 2, 1, 1);
    player1 = Paddle(1, screenHeight / 2 - 3, 2, 6);
    player2 = Paddle(screenWidth - 2, screenHeight / 2 - 3, 2, 6);

    gameObjects.push_back(&player1);
    gameObjects.push_back(&player2);
    gameObjects.push_back(&ball);
}

void Game::run() {
    try {
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
                    throw GameOverException("User quit the game.\n");
                }
                if (key == '=') {
                    try {
                        ball.performAction('=');
                    } catch (const std::exception &ex) {
                        std::cerr << "Error performing action on Ball: " << ex.what() << std::endl;
                    }
                }
                if (key == '-') {
                    try {
                        ball.performAction('-');
                    } catch (const std::exception &ex) {
                        std::cerr << "Error performing action on Ball: " << ex.what() << std::endl;
                    }
                }
            }

            for (GameObject *obj: gameObjects) {
                obj->update();
            }

            if (ball.isWithin(0, screenHeight - 1)) {
                ball.reverseY();
            }

            for (const GameObject *obj: gameObjects) {
                if (const auto *paddle = dynamic_cast<const Paddle *>(obj)) {
                    handlePaddleCollisions(*paddle, ball);
                }
            }

            if (ball.getX() < 0) {
                player2Score++;
                resetGame();
            } else if (ball.getX() >= screenWidth) {
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
    // rlutil::msleep(40);
    rlutil::locate(1, 1);
    std::cout << "Player 1 Score: " << getPlayer1Score() << " | Player 2 Score: " << getPlayer2Score() << std::endl;

    for (int i = -1; i <= screenHeight; i++) {
        renderBorder(i);
    }
}