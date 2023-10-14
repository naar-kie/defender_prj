#ifndef ENEMY_H
#define ENEMY_H

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

#endif
