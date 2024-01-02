//
// Created by Roby on 1/2/2024.
//

#ifndef OOP_GAMEEXCEPTIONS_H
#define OOP_GAMEEXCEPTIONS_H

#include <stdexcept>
#include <string>

class GameException : public std::exception {
public:
    virtual const char *what() const noexcept override {
        return "Game Exception";
    }
};

class InvalidInputException : public GameException {
private:
    std::string errorMessage;

public:
    explicit InvalidInputException(const std::string &message);

    const char *what() const noexcept override;
};

class GameOverException : public GameException {
private:
    std::string errorMessage;

public:
    explicit GameOverException(const std::string &message);

    const char *what() const noexcept override;
};

#endif // OOP_GAMEEXCEPTIONS_H
