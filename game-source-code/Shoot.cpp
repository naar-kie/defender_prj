#define _USE_MATH_DEFINES

#include "Shoot.h"
#include "Collision.h"
#include "Enemy.h"
#include "Player.h"
#include "Lander.h"
#include "Pod.h"
#include "Utilities.h"
#include "Entity.h"
#include <cmath>

namespace defender
{
    void Shoot::update(sf::Time deltaTime)
    {
        float screenRight = _world.getWidth();
        float screenBottom = _world.getHeight();
        sf::FloatRect bounds = _sprite.getGlobalBounds();
        float halfWidth = bounds.width / 2.0f;
        float halfHeight = bounds.height / 2.0f;

        float seconds = deltaTime.asSeconds();
        _sprite.move(seconds * _impulse);
        _duration -= deltaTime;

        // Check if the duration is less than zero or if the shoot is out of bounds
        if (_duration < sf::Time::Zero ||
            _sprite.getPosition().x < 0 + halfWidth || _sprite.getPosition().x > screenRight - halfWidth||
            _sprite.getPosition().y < 0 + halfHeight || _sprite.getPosition().y > screenBottom - halfHeight)
        {
            _alive = false;
        }
    }

/********** SHOOT PLAYER **********/
    ShootPlayer::ShootPlayer(Player &from) : Shoot(Setup::Textures::ShootPlayer, from._world)
    {
        _duration = sf::seconds(2);
        float angle = from._sprite.getRotation() / 180 * M_PI - M_PI_2;
        _impulse = sf::Vector2f(std::cos(angle), std::sin(angle)) * 500.f;
        setPosition(from.getPosition());
        _sprite.setRotation(from._sprite.getRotation());
    }

    bool ShootPlayer::isCollide(const Entity &other) const
    {
        return dynamic_cast<const Enemy *>(&other) != nullptr && Collision::circleTest(_sprite, other._sprite);
    }

/********** SHOOT LANDER **********/
    ShootLander::ShootLander(lander &from) : Shoot(Setup::Textures::ShootLander, from._world)
    {
        _duration = sf::seconds(5);

        // Calculate direction vector from lander to spaceship
        sf::Vector2f direction = Setup::player->getPosition() - from.getPosition();
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

        // Set impulse of the missile towards the spaceship
        if (length != 0) {
            direction /= length;
        }

        _impulse = direction * 500.f;

        setPosition(from.getPosition());

        float angle_rad = std::atan2(direction.y, direction.x);
        float angle_deg = angle_rad * 180 / M_PI;
        _sprite.setRotation(angle_deg + 90);

    }

    bool ShootLander::isCollide(const Entity &other) const
    {
        return (dynamic_cast<const Player *>(&other) || dynamic_cast<const Pod *>(&other)) &&
               Collision::circleTest(_sprite, other._sprite);
    }
}
