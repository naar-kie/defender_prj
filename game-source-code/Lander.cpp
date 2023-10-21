#include <cmath>
#include "Collision.h"
#include "Shoot.h"
#include "Enemy.h"
#include "Player.h"
#include "Lander.h"
#include "Pod.h"
#include "Utilities.h"

namespace defender
{

    bool Lander::isCollide(const Entity &other) const
    {
        if(dynamic_cast<const Enemy *>(&other) == nullptr && dynamic_cast<const ShootLander *>(&other) == nullptr) {
         return Collision::circleTest(_sprite,other._sprite);
         }
        return false;

    }

    /** manages the movement of the Lander by:
     * 1. looking for the nearest object of the Lander into which it may crash
     * 2. If there is an object found too close, impulse is added to the Lander
     *    in the opposite direction of this object. The goal is to avoid a crash.
    */
    void Lander::update(sf::Time deltaTime)
    {
        float seconds = deltaTime.asSeconds();
        Entity *near = nullptr;
        float near_distance = 300;
        for (Entity *entityPtr : _world.getEntities())
        {
            if (entityPtr != this && (dynamic_cast<const Pod *>(entityPtr) ||
                                      dynamic_cast<const ShootPlayer *>(entityPtr)))
            {
                float x = getPosition().x - entityPtr->getPosition().x;
                float y = getPosition().y - entityPtr->getPosition().y;
                float dist = std::sqrt(x * x + y * y);
                if (dist < near_distance)
                {
                    near_distance = dist;
                    near = entityPtr;
                }
            }
        }
        if (near != nullptr)
        {
            sf::Vector2f pos = near->getPosition() - getPosition();
            float angle_rad = std::atan2(pos.y, pos.x);
            _impulse -= sf::Vector2f(std::cos(angle_rad), std::sin(angle_rad)) * 180.f * seconds;
        }
        else
        {
            sf::Vector2f pos = Setup::player->getPosition() - getPosition();
            float angle_rad = std::atan2(pos.y, pos.x);
            _impulse += sf::Vector2f(std::cos(angle_rad), std::sin(angle_rad)) * 100.f * seconds;
        }
        _sprite.move(seconds * _impulse);
    }

    void Lander::onDestroy()
    {
        Enemy::onDestroy();
        Setup::maxLanders--;
        newLander(_world);
    }

    // This function will randomly create a Lander depending on the player's score and add it to the world
    void Lander::newLander(World &world)
    {
        Lander *res = nullptr;
        res = new lander(world);
        res->setPosition(Utilities::random(0, 1) * world.getWidth(),
                         Utilities::random(0.f, (float) world.getHeight()));
        world.add(res);
    }

/********** creating a Lander **********/
    // move the Lander by calling the update() function from the Lander base, then shoot the player as soon as we can
    lander::lander(World &world) : Lander(Setup::Textures::lander, world)
    {
        _timeSinceLastShoot = sf::Time::Zero;
        _impulse *= 100.f; // initialize the impulsion
    }

    int lander::getPoints() const
    {
        return 200;
    }

    void lander::update(sf::Time deltaTime)
    {
        Lander::update(deltaTime);
        _timeSinceLastShoot += deltaTime;
        if (_timeSinceLastShoot > sf::seconds(1.5))
        {
            if (Setup::player != nullptr)
                _world.add(new ShootLander(*this));
            _timeSinceLastShoot = sf::Time::Zero;
        }
    }
}