/**
 * @file main.cpp
 * @author Kgadile Masemola (876729), Jashna Gurahoo (2309262)
 * @brief This file executes the game
 * @version 3.0
 * @date 2023-10-12
 * 
 * 
 */

#include "Game.h"

/**
 * @brief The main function, the entry point for the Game.
 *
 * This function initializes the game and starts its execution.
 *
 * @return An integer value representing the exit status (0 for success).
 */

//using namespace defender;

int main()
{
    defender::Setup::initialize();

    defender::Game game(1280, 800);
    game.run();

    return 0;

}