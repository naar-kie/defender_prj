#ifndef GAME_H
#define GAME_H

/**
 * @file Game.h
 * @brief Class that mangages all the game logic
 */

#include <SFML/Graphics.hpp>
#include "World.h"
#include <ctime>

namespace defender
{
    class Game
    {
    public:
        /**
         * This feature lets us delete the copy constructor and operator,
         * which makes this class non-copyable. We only want one game.
         * We tell to the compiler to not build the default function
         */
        Game(const Game &) = delete;
        Game &operator=(const Game &) = delete;

        Game(unsigned int width = 800, unsigned int height = 600);
        void run(int minFPS = 60);

        void initLevel();
        sf::Text _text;


    private:
        void processEvents();
        void update(sf::Time deltaTime);
        void render();

        void reset();

        sf::RenderWindow _window;
        World _world;

        sf::Time _nextLander;
    };
}

#endif
