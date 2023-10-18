/**
 * @file World.h
 *
 * Defines the game world and handles entities within it.
 */
#ifndef WORLD_H
#define WORLD_H

#include <SFML/Graphics.hpp>
#include "Setup.h"
#include <memory>
#include <list>

namespace defender
{

    /**
     * @class World
     * @brief Represents the game world and manages entities within it.
    * The World class manages the entities, their updates, collisions, and rendering within the game world.

     */
    class Entity;
    class World : public sf::Drawable
    {
    public:
        /**
         * @brief Constructs a World object.
         * @param width Width of the game world.
         * @param height Height of the game world.
          * @brief Adds an entity to the world.
         * @param entity Pointer to the entity to be added.
         */
        /**
         * This c++11 feature lets us delete the copy constructor and operator,
         * which makes this class non-copyable.
         */
                 // ... public member functions and variables ...

        World(const World &) = delete;
        World &operator=(const World &) = delete;

        World(int width, int height); // this sets the size of the world
        /**
         * @brief Destructor for the World class.
         * Clears the entities from the world.
         */
        ~World(); // clears the world

        void add(Entity *entity); // add entities to a temporary container
        /**
         * @brief Clears all entities from the world.
         */

        void clear(); // delete all entities manually -> to be changed using unique pointers
        /**
         * @brief Checks if the given entity collides with any other entity in the world.
         * @param other Entity to check collision against.
         * @return True if there is a collision, false otherwise.
         */

        bool isCollide(const Entity &other); //check whether the entity is colliding with another
        /**
         * @brief Gets the number of entities in the world.
         * @return Number of entities.
         */
        int size(); // returns number of entities
        // ... public member functions and variables ...

        /**
         * @brief Updates the world based on the elapsed time.
         * @param deltaTime Time passed since the last update.
         */

        const std::list<Entity *> getEntities() const;
        int getWidth() const;
        int getHeight() const;

        // ... member functions and variables ...

        /**
         * @brief Updates the game world based on the time passed.
         * @param deltaTime Time passed since the last update.
         */
        void update(sf::Time deltaTime); // see function declaration
        sf::Clock _gameClock;
        const int _width, _height; /**< Width and height of the game world. */


    private:
                // ... private member functions and variables ...

        /**
         * @brief Draws the entities in the world.
         * @param target Render target to draw on.
         * @param states Current render states.
         */

        std::list<Entity *> _entities;/**< List of entities currently in the world. */
        std::list<Entity *> _entitiesTemp;/**< Temporary list for holding newly created entities. */


        virtual void draw(sf::RenderTarget &target, sf::RenderStates) const override;

    };
    };


#endif
