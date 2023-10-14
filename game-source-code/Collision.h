#ifndef COLLISION_H
#define COLLISION_H

#include <SFML/Graphics.hpp>

namespace defender
{
    class Collision // tests collisions between cirlcles
    {
    public:
        Collision() = delete;
        Collision(const Collision &) = delete;
        Collision &operator=(const Collision &) = delete;

        static bool circleTest(const sf::Sprite &first, const sf::Sprite &seconds);
    };
}

#endif
