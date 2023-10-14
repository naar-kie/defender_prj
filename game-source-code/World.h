#ifndef WORLD_H
#define WORLD_H

#include <SFML/Graphics.hpp>
#include "Setup.h"
#include <memory>
#include <list>

namespace defender
{
    class Entity;
    class World : public sf::Drawable
    {
    public:
        /**
         * This c++11 feature lets us delete the copy constructor and operator,
         * which makes this class non-copyable.
         */
        World(const World &) = delete;
        World &operator=(const World &) = delete;

        World(int width, int height); // this sets the size of the world
        ~World(); // clears the world

        void add(Entity *entity); // add entities to a temporary container
        void clear(); // delete all entities manually -> to be changed using unique pointers

        bool isCollide(const Entity &other); //check whether the entity is colliding with another
        int size(); // returns number of entities

        const std::list<Entity *> getEntities() const;
        int getWidth() const;
        int getHeight() const;

        void update(sf::Time deltaTime); // see function declaration
        sf::Clock _gameClock;

    private:
        std::list<Entity *> _entities;
        std::list<Entity *> _entitiesTemp;

        virtual void draw(sf::RenderTarget &target, sf::RenderStates) const override;

        const int _width, _height;
    };
}

#endif
