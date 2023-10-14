#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include "Setup.h"

namespace defender
{
    class World;
    class Entity : public sf::Drawable
    {
    public:
        /**
         * This c++11 feature lets us delete the copy constructor and operator,
         * which makes this class non-copyable.
         */
        Entity(const Entity &) = delete;
        Entity &operator=(const Entity &) = delete;

        Entity(Setup::Textures textureID, World &world);
        virtual ~Entity() {} // virtual destructor because the class will be polymorphic

        virtual bool isAlive() const; // check if Entity is alive
        virtual bool isCollide(const Entity &other) const = 0;

        const sf::Vector2f &getPosition() const;
        template<typename ... Args>
        void setPosition(Args &&... args)
        {
            _sprite.setPosition(std::forward<Args>(args) ...);
        }

        sf::FloatRect getGlobalBounds() const {
            return _sprite.getGlobalBounds();
        }

        virtual void update(sf::Time deltaTime) = 0;
        virtual void onDestroy();

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
