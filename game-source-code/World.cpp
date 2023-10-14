#include "World.h"
#include "Entity.h"
#include "Pod.h"
#include "Lander.h"
#include "Game.h"
#include "Setup.h"

namespace defender
{
    World::World(int width, int height) : _width(width), _height(height)
    {
    }

    World::~World()
    {
        clear();
    }

    void World::add(Entity *entity)
    {
        _entitiesTemp.push_back(entity); // temp bcoz some entities may create other entities to avoid breaking iterator
    }

    void World::clear()
    {
        for (Entity *entity : _entities)
            delete entity;
        _entities.clear();

        for (Entity *entity : _entitiesTemp)
            delete entity;
        _entitiesTemp.clear();

    }

    bool World::isCollide(const Entity &other)
    {
        for (Entity *entityPtr : _entities)
            if (other.isCollide(*entityPtr))
                return true;
        return false;
    }

    int World::size()
    {
        return _entities.size() + _entitiesTemp.size();
    }

    const std::list<Entity *> World::getEntities() const
    {
        return _entities;
    }

    int World::getWidth() const
    {
        return _width;
    }

    int World::getHeight() const
    {
        return _height;
    }

    void World::update(sf::Time deltaTime)
    {

        if (_entitiesTemp.size() > 0) // merge entities together into main container
            _entities.merge(_entitiesTemp);

        for (Entity *entityPtr : _entities) // update entities and verify the correct position within world
        {
            Entity &entity = *entityPtr;
            entity.update(deltaTime);

             // Calculate the effective width and height including the centered origin
            sf::FloatRect bounds = entity.getGlobalBounds();
            float halfWidth = bounds.width / 2.0f;
            float halfHeight = bounds.height / 2.0f;

            sf::Vector2f pos = entity.getPosition();

            // Adjust the position based on the entity's half dimensions
            if (pos.x - halfWidth < 0) {
                pos.x = halfWidth;
            } else if (pos.x + halfWidth > _width) {
                pos.x = _width - halfWidth;
            }
            if (pos.y - halfHeight < 0) {
                pos.y = halfHeight;
            } else if (pos.y + halfHeight > _height) {
                pos.y = _height - halfHeight;
            }
            entity.setPosition(pos);
        }

        const auto end = _entities.end();
        for (auto it_i = _entities.begin(); it_i != end; ++it_i)
        {
            Entity &entity_i = **it_i; // check collision between all entities
            auto it_j = it_i;
            it_j++;
            for (; it_j != end; ++it_j)
            {
                Entity &entity_j = **it_j;

                if (entity_i.isAlive() && entity_i.isCollide(entity_j))
                    entity_i.onDestroy();

                if (entity_j.isAlive() && entity_j.isCollide(entity_i))
                    entity_j.onDestroy();
            }
        }

        for (auto it = _entities.begin(); it != _entities.end();) // delete dead entities
        {
            if (!(*it)->isAlive())
            {
                delete *it;
                it = _entities.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }

    void World::draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        for (Entity *entity : _entities)
            target.draw(*entity, states);
    }
}
