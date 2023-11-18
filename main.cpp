#include <iostream>
#include "rlutil.h"

enum GameStatus
{
    START = 1,
    QUIT = 2
};

class Paddle
{
private:
    int x, y;
    int width, height;
public:
    Paddle(int startX, int startY, int paddleWidth, int paddleHeight):
            x(startX), y(startY),
            width(paddleWidth), height(paddleHeight) {}

    Paddle(const Paddle& other) : x(other.x), y(other.y), width(other.width), height(other.height) {}

    Paddle& operator=(const Paddle& other)
    {
        this->x = other.x;
        this->y = other.y;
        this->width = other.width;
        this->height = other.height;
        return *this;
    }

    ~Paddle() {}

    friend std::ostream& operator<<(std::ostream& os, const Paddle& paddle);

    int getX() const
    {
        return x;
    }

    int getY() const
    {
        return y;
    }

    int getWidth() const
    {
        return width;
    }

    int getHeight() const
    {
        return height;
    }

    void moveUp()
    {
        if (y > 0)
        {
            y--;
        }
    }

    void moveDown(int screenHeight)
    {
        if (y + height < screenHeight)
        {
            y++;
        }
    }
};

class Ball
{
private:
    double x, y;
    double xSpeed, ySpeed;
public:
    Ball(int startX, int startY)
            : x(startX), y(startY), xSpeed(1), ySpeed(1) {}

    int getX() const
    {
        return x;
    }
    int getY() const
    {
        return y;
    }

    void update()
    {
        x = x + xSpeed;
        y = y + ySpeed;
    }

    void reverseX()
    {
        xSpeed = -xSpeed;
    }

    void reverseY()
    {
        ySpeed = -ySpeed;
    }

    bool isWithin(int minY, int maxY)
    {
        return (y < minY || y > maxY);
    }

    friend std::ostream& operator<<(std::ostream& os, const Ball& ball);
};

class Game
{
private:
    int screenWidth, screenHeight;
    Paddle player1, player2;
    Ball ball;
public:
    Game(int width, int height) :
            screenWidth(width), screenHeight(height),
            player1(1, screenHeight / 2 - 3, 1, 6),
            player2(screenWidth - 2, screenHeight / 2 - 3, 1, 6),
            ball(screenWidth / 2, screenHeight / 2)
    {
        rlutil::hidecursor();
    }

    friend std::ostream &operator<<(std::ostream &os, const Game &pingPongGame);

        void handlePaddleCollisions(const Paddle &paddle, const Ball &gameBall)
    {
        if (gameBall.getX() == paddle.getX() && ball.getY() >= paddle.getY() &&
            ball.getY() < paddle.getY() + paddle.getHeight())
        {
            ball.reverseX();
        }
    }

    void resetGame()
    {
        ball = Ball(screenWidth / 2, screenHeight / 2);
        player1 = Paddle(1, screenHeight / 2 - 3, 1, 6);
        player2 = Paddle(screenWidth - 2, screenHeight / 2 - 3, 1, 6);
    }


    void run()
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

    void renderBorder(int row)
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

    void renderGameElements(int row, int col)
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

    void render()
    {
        rlutil::msleep(40);
        rlutil::locate(1, 1);

        for (int i = -1; i <= screenHeight; i++)
        {
            renderBorder(i);
        }
    }
};

void instructions()
{
    std::cout << "1 - Start a new game"<<std::endl;
    std::cout << "2 - Stop the game"<<std::endl;
    std::cout << "Q - To exit while in game "<<std::endl;
    std::cout << "---How to play---"<<std::endl;
    std::cout << "Player 1 (left): w -> go up / s -> go down"<<std::endl;
    std::cout << "Player 2 (right): i -> go up / j -> go down"<<std::endl;
    std::cout << "Enter option: ";
    rlutil::hidecursor();
}

std::ostream& operator<<(std::ostream& os, const Paddle& paddle)
{
    os << "Paddle position (x, y): (" << paddle.x << ", " << paddle.y << ")\n";
    os << "Paddle dimensions (width, height): (" << paddle.width << ", " << paddle.height << ")\n";
    return os;
}

std::ostream& operator<<(std::ostream& os, const Ball& ball)
{
    os << "Ball position (x, y): (" << ball.x << ", " << ball.y << ")\n";
    os << "Ball speed(x_speed, y_speed): (" <<ball.xSpeed << ", " << ball.ySpeed << ")\n";
    return os;
}

std::ostream& operator<<(std::ostream& os, const Game& game)
{
    os << "Screen Dimensions: " << game.screenWidth << "x" << game.screenHeight << "\n";
    os << "Player 1:\n" << game.player1;
    os << "Player 2:\n" << game.player2;
    os << "Ball Position: (" << game.ball.getX() << ", " << game.ball.getY() << ")\n";
    return os;
}

int main()
{
    GameStatus status = START;

    while (status == START)
    {
        instructions();
        char choice;
        std::cin >> choice;

        if (choice == '2')
        {
            status = QUIT;
        }
        else if (choice == '1')
        {
            Game pingPongGame(rlutil::tcols() - 2,rlutil::trows() - 3);
            pingPongGame.run();
        }
        else
        {
            std::cout << "Invalid choice. Please choose 1 to start a game or 2 to quit." << "\n\n";
        }
    }

    rlutil::showcursor();
    return 0;
}
