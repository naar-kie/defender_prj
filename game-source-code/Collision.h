/**
 * @file Collision.h
 *
 * Provides collision detection functions.
 */
#ifndef COLLISION_H
#define COLLISION_H

#include <SFML/Graphics.hpp>

namespace defender
{
    /**
     * @class Collision
     * @brief Provides static functions for collision detection.
     */
    class Collision // tests collisions between cirlcles
    {
    public:
                // ... public member functions and variables ...

        /**
         * @brief Performs a circle-to-circle collision test.
         * @param spriteA First sprite to check for collision.
         * @param spriteB Second sprite to check for collision.
         * @return True if the sprites collide, false otherwise.
         */
        Collision() = delete;
        Collision(const Collision &) = delete;
        Collision &operator=(const Collision &) = delete;

        static bool circleTest(const sf::Sprite &first, const sf::Sprite &seconds);
    };
}

#endif
