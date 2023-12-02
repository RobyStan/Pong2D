#include "Game.h"

enum GameStatus
{
    START = 1,
    QUIT = 2
};

void instructions()
{
    std::cout << "1 - Start a new game"<<std::endl;
    std::cout << "2 - Quit the game"<<std::endl;
    std::cout << "Q - To exit while in game "<<std::endl;
    std::cout << "---How to play---"<<std::endl;
    std::cout << "Player 1 (left): w -> go up / s -> go down"<<std::endl;
    std::cout << "Player 2 (right): i -> go up / j -> go down"<<std::endl;
    std::cout << "Enter option: ";
    rlutil::hidecursor();
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
            std::cout << "\nInvalid choice. Please choose 1 to start a game or 2 to quit." << "\n\n";
        }
    }

    rlutil::showcursor();
    return 0;
}
