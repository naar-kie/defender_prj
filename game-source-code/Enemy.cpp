#define _USE_MATH_DEFINES
#include "Enemy.h"
#include "Utilities.h"
#include <cmath>

namespace defender
{
    Enemy::Enemy(Setup::Textures textureID, World &world) : Entity(textureID, world)
    {
        float angle = Utilities::random(0.f, 2.f * M_PI);
        _impulse = sf::Vector2f(std::cos(angle), std::sin(angle));
    }

    // adds the points won by destroying the object
    void Enemy::onDestroy()
    {
        Entity::onDestroy();
        Setup::addScore(getPoints());
    }
}
