//
// Created by Roby on 1/2/2024.
//


#include "GameExceptions.h"

InvalidInputException::InvalidInputException(const std::string &message)
        : errorMessage(message) {}

const char *InvalidInputException::what() const noexcept {
    return errorMessage.c_str();
}

GameOverException::GameOverException(const std::string &message)
        : errorMessage(message) {}

const char *GameOverException::what() const noexcept {
    return errorMessage.c_str();
}