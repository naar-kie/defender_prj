#ifndef LANDER_H
#define LANDER_H

#include "Enemy.h"

namespace defender
{
    class Lander : public Enemy
    {
    public:
        Lander(World &world);
        Lander(const Lander &) = delete;
        Lander &operator=(const Lander &) = delete;

        using Enemy::Enemy; // the class will not specify the constructor, we use the the one from Enemy

        virtual bool isCollide(const Entity &other) const;
        virtual void update(sf::Time deltaTime);
        virtual void onDestroy();

        static void newLander(World &world);
        static int landersDestroyed; // Static variable to keep track of destroyed landers

    };

    class lander : public Lander
    {
    public:
        lander(World &world);
        virtual int getPoints() const;
        virtual void update(sf::Time deltaTime);
    private:
        sf::Time _timeSinceLastShoot;
    };
}

#endif
