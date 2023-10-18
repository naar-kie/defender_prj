#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include "Setup.h"

namespace defender

/**
     * @class Entity
     * @brief The base class for all game entities.
     */
{
    class World;
    class Entity : public sf::Drawable
    {
    public:
                // ... public member functions and variables ...

        /**
         * This feature lets us delete the copy constructor and operator,
         * which makes Entities of this class non-copyable.
         */
        Entity(const Entity &) = delete;
        Entity &operator=(const Entity &) = delete;

       /**
         * @brief Default constructor for Entity.
         * @param texture The texture for the entity.
         * @param world Reference to the game world.
         */
        Entity(Setup::Textures textureID, World &world);
        virtual ~Entity() {} // virtual destructor because the class will be polymorphic

        /**
         * @brief Get the global bounding rectangle of the entity.
         * @return sf::FloatRect The bounding rectangle.
         */
        virtual bool isAlive() const; // check if Entity is alive
         /**
         * @brief Virtual function to update the entity based on elapsed time.
         * @param deltaTime Time elapsed since the last update.
         */
        virtual bool isCollide(const Entity &other) const = 0;

        const sf::Vector2f &getPosition() const;
        /**
         * @brief Set the position of the entity. using the Variadic template so that 
         *  both of the sf::Transformable::setPosition() functions can be used
         * @param position The new position of the entity.
         */
        template<typename ... Args>
        void setPosition(Args &&... args)
        {
            _sprite.setPosition(std::forward<Args>(args) ...);/**
         * @brief forward the parameters to sf::Transformable::setPosition()
         * @return bool True if the entity is alive, false otherwise.
         */
        }

        sf::FloatRect getGlobalBounds() const {
            return _sprite.getGlobalBounds();
        }
        /**
         * @brief Get the position of the entity.
         * @return sf::Vector2f The position of the entity.
         */

        virtual void update(sf::Time deltaTime) = 0;
        /**
         * @brief Virtual function to handle collision with another entity.
         * @param other The other entity to check collision with.
         * @return bool True if a collision occurs, false otherwise.
         */
        virtual void onDestroy();
        /**
         * @brief Virtual function to draw the entity on the render target.
         * @param target The target to draw the entity on.
         * @param states The render states to use for drawing.
         */

    protected:
        friend class Lander;
        friend class Pod;
        friend class Player;
        friend class ShootPlayer;
        friend class ShootLander;

        sf::Sprite _sprite;
        sf::Vector2f _impulse;
        World &_world;
        bool _alive;

    private:
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    };
}

#endif
