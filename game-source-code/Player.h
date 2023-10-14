#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "ActionTarget.h"
#include "Entity.h"
#include "World.h"

namespace defender
{
    class Player : public Entity, public ActionTarget<int>
    {
    public:
        /**
         * This c++11 feature lets us delete the copy constructor and operator,
         * which makes this class non-copyable. Only want one player.
         */
        Player(const Player &) = delete;
        Player &operator=(const Player &) = delete;

        Player(World &world);

        virtual bool isCollide(const Entity &other) const;
        virtual void update(sf::Time deltaTime);
        virtual void onDestroy();

        void processEvents();
        void shoot();

        bool moveUp = 0, moveDown = 0, moveLeft = 0, moveRight = 0; // mine


    private:
        float shipSpeed = 350.f;
        int _rotation;
        int direction;
        bool facedRight = true;
        bool facedLeft = false;
        sf::Time _timeSinceLastShoot;
        sf::Vector2f movement;

        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    };
}

#endif
