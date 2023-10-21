#ifndef ENEMY_H
#define ENEMY_H

/**
 * @file Enemy.h
 * @brief Base class for all enemy/Allien Entites
 */

#include "Entity.h"

namespace defender
{
    class Enemy : public Entity
    {
    public:
        /**
         * This c++11 feature lets us delete the copy constructor and operator,
         * which makes this class non-copyable.
         */
        Enemy(const Enemy &) = delete;
        Enemy &operator=(const Enemy &) = delete;

        Enemy(Setup::Textures textureID, World &world);

        virtual int getPoints() const = 0;
        virtual void onDestroy();
    };
}

#endif // class adapted from iZastic on 27/09/2023, Created on 11/8/2015.
