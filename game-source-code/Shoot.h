/**
 * @file Shoot.h
 *
 * Defines shoot entities for both player and enemies.
 */
#ifndef SHOOT_H
#define SHOOT_H

#include "Entity.h"

namespace defender
{
    /**
     * @class Shoot
     * @brief Represents a shoot entity in the game.
     */
    class Shoot : public Entity
    {
    public:
        /**
         * @brief Constructs a Shoot object.
         * @param id Texture identifier for the shoot.
         * @param world Reference to the game world.
         */
        Shoot(const Shoot &) = delete;
        Shoot &operator=(const Shoot &) = delete;

        using Entity::Entity;

        virtual void update(sf::Time deltaTime);

    protected:
        sf::Time _duration;
    };
 /**
     * @class ShootPlayer
     * @brief Represents a shoot entity from the player.
     */
    class ShootPlayer : public Shoot
    {
    public :
        /**
         * @brief Constructs a ShootPlayer object.
         * @param from Reference to the player shooting.
         */
        // ... public member functions and variables ...

        /**
         * @brief Checks if the shoot collides with an enemy entity.
         * @param other Entity to check collision against.
         * @return True if the shoot collides with the enemy, false otherwise.
         */

        ShootPlayer(const ShootPlayer &) = delete;
        ShootPlayer &operator=(const ShootPlayer &) = delete;
        ShootPlayer(Player &from);
        // ... member functions ...

        /**
         * @brief Checks if the projectile collides with an enemy entity.
         * @param other The other entity to check collision with.
         * @return True if there is a collision, false otherwise.
         */
        virtual bool isCollide(const Entity &other) const;
        /**
     * @class ShootLander
     * @brief Represents a shooting entity fired by enemy lander entities.
     */
    };

    /**
     * @class ShootLander
     * @brief Represents a shoot entity from lander enemies.
     */
    class lander;
    class ShootLander : public Shoot
    {
        /**
         * @brief Checks if the shoot collides with the player or a pod entity.
         * @param other Entity to check collision against.
         * @return True if the shoot collides with the player or pod, false otherwise.
         */
    public :
         /**
         * @brief Constructs a ShootLander object.
         * @param from Reference to the lander shooting.
         */
        ShootLander(const ShootLander &) = delete;
        ShootLander &operator=(const ShootLander &) = delete;

        ShootLander(lander &from);
        // ... member functions ...

        /**
         * @brief Checks if the projectile collides with the player or pod entities.
         * @param other The other entity to check collision with.
         * @return True if there is a collision, false otherwise.
         */

        virtual bool isCollide(const Entity &other) const;
    };
}

#endif
