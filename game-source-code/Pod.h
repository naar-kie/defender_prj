#ifndef POD_H
#define POD_H

#include "Enemy.h"

namespace defender
{
    class Pod : public Enemy
    {
    public:
        Pod(const Pod &) = delete;
        Pod &operator=(const Pod &) = delete;
        using Enemy::Enemy;

        virtual bool isCollide(const Entity &other) const;
        virtual void update(sf::Time deltaTime);
    protected:
        float _rotation;
    };

    class BigPod : public Pod
    {
    public :
        BigPod(World &world);
        virtual int getPoints() const;
        virtual void onDestroy();
    };

    class Swarmer : public Pod
    {
    public :
        Swarmer(World &world);
        virtual void update(sf::Time deltaTime);
        virtual int getPoints() const;
        virtual void onDestroy();
    };
}

#endif
