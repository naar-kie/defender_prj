#include "Collision.h"
#include "Pod.h"
#include "World.h"
#include "Player.h"
#include "Utilities.h"
#include "Lander.h"
#include "Shoot.h"
#include <cmath>

namespace defender
{
    bool Pod::isCollide(const Entity &other) const
    {
        if(dynamic_cast<const Pod*>(&other) == nullptr) {
        return Collision::circleTest(_sprite,other._sprite);
        }
        //return dynamic_cast<const ShootLander *>(&other) == nullptr && Collision::circleTest(_sprite, other._sprite);
        return false;
    }

    void Pod::update(sf::Time deltaTime)
    {
        if (Setup::player) {
        sf::Vector2f playerPosition = Setup::player->getPosition();
        sf::Vector2f direction = playerPosition - _sprite.getPosition();
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

        if (length != 0) {
            direction /= length;
        }

        float speed= 100.f;
            // Move the Pod towards the Player
            _sprite.move(direction * speed * deltaTime.asSeconds());
        }
    }

    BigPod::BigPod(World &world) :
            Pod((Setup::Textures) Utilities::random(Setup::Textures::BigPod1,
                                                           Setup::Textures::BigPod4), world)
    {
        _impulse *= 100.f;
        //_rotation = Utilities::random(0.025f, 0.05f);
    }

    int BigPod::getPoints() const
    {
        return 20;
    }

    void BigPod::onDestroy()
    {
        Pod::onDestroy();
        int sm = 3; // Number of Swarmers to spawn

        for (int i = 0; i < sm; ++i)
        {
            Swarmer *swarmer = new Swarmer(_world);
            swarmer->setPosition(getPosition());
            _world.add(swarmer);
        }
    }

    Swarmer::Swarmer(World &world) :
            Pod((Setup::Textures) Utilities::random(Setup::Textures::Swarmer1,
                                                           Setup::Textures::Swarmer4), world)
    {

        //set a smaller scale for swarmers
        _sprite.setScale(0.5f, 0.5f);

    }

    void Swarmer::update(sf::Time deltaTime)
    {
        if (Setup::player) {
        sf::Vector2f playerPosition = Setup::player->getPosition();
        sf::Vector2f direction = playerPosition - _sprite.getPosition();
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

        if (length != 0) {
            direction /= length;
        }

        float speed= 300.f;
        // Move the Pod towards the Player
        _sprite.move(direction * speed * deltaTime.asSeconds());

        }
    }

    int Swarmer::getPoints() const
    {
        return 100;
    }

    void Swarmer::onDestroy()
    {
        Pod::onDestroy();
    }
}
