//
// Created by Adriana on 12/2/2023.
//

#include "Game.h"

Game::Game(int width, int height) :
        screenWidth(width), screenHeight(height),
        player1(1, screenHeight / 2 - 3, 1, 6),
        player2(screenWidth - 2, screenHeight / 2 - 3, 1, 6),
        ball(screenWidth / 2, screenHeight / 2)
{
    rlutil::hidecursor();
}

std::ostream& operator<<(std::ostream& os, const Game& game)
{
    os << "Screen Dimensions: " << game.screenWidth << "x" << game.screenHeight << "\n";
    os << "Player 1:\n" << game.player1;
    os << "Player 2:\n" << game.player2;
    os << "Ball Position: (" << game.ball.getX() << ", " << game.ball.getY() << ")\n";
    return os;
}

void Game::handlePaddleCollisions(const Paddle &paddle, const Ball &gameBall)
{
    if (gameBall.getX() == paddle.getX() && ball.getY() >= paddle.getY() &&
        ball.getY() < paddle.getY() + paddle.getHeight())
    {
        ball.reverseX();
    }
}

void Game::resetGame()
{
    ball = Ball(screenWidth / 2, screenHeight / 2);
    player1 = Paddle(1, screenHeight / 2 - 3, 1, 6);
    player2 = Paddle(screenWidth - 2, screenHeight / 2 - 3, 1, 6);
}

void Game::run()
{
    while (true)
    {
        if (kbhit())
        {
            int key = std::tolower(rlutil::getkey());
            if (key == 'w')
            {
                player1.moveUp();
            }
            if (key == 's')
            {
                player1.moveDown(screenHeight);
            }
            if (key == 'i')
            {
                player2.moveUp();
            }
            if (key == 'j')
            {
                player2.moveDown(screenHeight);
            }
            if (key == 'q')
            {
                break;
            }
        }

        ball.update();

        if (ball.isWithin(0, screenHeight - 1))
        {
            ball.reverseY();
        }

        handlePaddleCollisions(player1, ball);
        handlePaddleCollisions(player2, ball);

        if (ball.getX() < 0 || ball.getX() >= screenWidth - 1)
        {
            resetGame();
        }

        render();
    }
}

void Game::renderBorder(int row)
{
    for (int j = 0; j < screenWidth; j++)
    {
        if (row == -1 || row == screenHeight)
        {
            std::cout << "~";
        }
        else
        {
            renderGameElements(row, j);
        }
    }
    std::cout << std::endl;
}

void Game::renderGameElements(int row, int col)
{
    if ((col == player1.getX() || col == player1.getX() + player1.getWidth() - 1) &&
        (row >= player1.getY() && row < player1.getY() + player1.getHeight()))
    {
        std::cout << "|";
    }
    else if ((col == player2.getX() || col == player2.getX() + player2.getWidth() - 1) &&
             (row >= player2.getY() && row < player2.getY() + player2.getHeight()))
    {
        std::cout << "|";
    }
    else if (col == ball.getX() && row == ball.getY())
    {
        std::cout << "O";
    }
    else
    {
        std::cout << " ";
    }
}

void Game::render()
{
    rlutil::msleep(40);
    rlutil::locate(1, 1);

    for (int i = -1; i <= screenHeight; i++)
    {
        renderBorder(i);
    }
}


