#ifndef SHOOT_H
#define SHOOT_H

#include "Entity.h"

namespace defender
{
    class Shoot : public Entity
    {
    public:
        Shoot(const Shoot &) = delete;
        Shoot &operator=(const Shoot &) = delete;

        using Entity::Entity;

        virtual void update(sf::Time deltaTime);

    protected:
        sf::Time _duration;
    };

    class ShootPlayer : public Shoot
    {
    public :
        ShootPlayer(const ShootPlayer &) = delete;
        ShootPlayer &operator=(const ShootPlayer &) = delete;
        ShootPlayer(Player &from);
        virtual bool isCollide(const Entity &other) const;
    };

    class lander;
    class ShootLander : public Shoot
    {
    public :
        ShootLander(const ShootLander &) = delete;
        ShootLander &operator=(const ShootLander &) = delete;

        ShootLander(lander &from);
        virtual bool isCollide(const Entity &other) const;
    };
}

#endif
