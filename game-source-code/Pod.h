/**
 * @file Pod.h
 *
 * Defines various pod entities for the game.
 */
#ifndef POD_H
#define POD_H

#include "Enemy.h"

namespace defender
{/**
     * @class Pod
     * @brief Represents the base class for pod entities.
     * The Pod class handles pod enemy behavior and collision detection.

     */
    class Pod : public Enemy
    {
    public:
        // ... constructors, member functions, and variables ...

        Pod(const Pod &) = delete;
        Pod &operator=(const Pod &) = delete;
        using Enemy::Enemy;

        virtual bool isCollide(const Entity &other) const;
        virtual void update(sf::Time deltaTime);
    protected:
        float _rotation;/**< Rotation angle of the pod. */
    };
    /**
     * @class BigPod
     * @brief Represents a larger pod entity in the game.
     */

    class BigPod : public Pod
    {
    public :
        /**
         * @brief Constructor for BigPod class.
         * @param world Reference to the game world.
         */
        BigPod(World &world);
        // ... member functions and variables ...

        /**
         * @brief Gets the points earned when BigPod is destroyed.
         * @return Points earned.
         */
        virtual int getPoints() const;
        /**
         * @brief Handles behavior when BigPod is destroyed, spawning Swarmer entities.
         */
        virtual void onDestroy();
    };

    /**
     * @class Swarmer
     * @brief Represents a swarmer enemy entity.
     */
    class Swarmer : public Pod
    {
    public :
        /**
         * @brief Constructor for Swarmer class.
         * @param world Reference to the game world.
         */
        Swarmer(World &world);
        /**
         * @brief Gets the points earned when Swarmer is destroyed.
         * @return Points earned.
         */
        virtual void update(sf::Time deltaTime);
        virtual int getPoints() const;
        /**
         * @brief Handles behavior when Swarmer is destroyed.
         */
        virtual void onDestroy();

        // private:
        //     int swarmersKilled = 0;
    };
    /**
     * @class Swarmer
     * @brief Represents a swarmer pod entity in the game.
     */
}

#endif
