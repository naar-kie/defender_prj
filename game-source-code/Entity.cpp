#include "Entity.h"
#include "World.h"

namespace defender
{
    // sets the texture to sf::sprite function and center it's origin
    Entity::Entity(Setup::Textures textureID, World &world) : _world(world), _alive(true)
    {
        sf::Texture &texture = Setup::textures.get(textureID);
        texture.isSmooth();
        _sprite.setTexture(texture);
        _sprite.setRotation(90);
        _sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
    }

    // check if entity is alive
    bool Entity::isAlive() const
    {
        return _alive;
    }

    const sf::Vector2f &Entity::getPosition() const
    {
        return _sprite.getPosition();
    }

    // called when collision is detected and do things that needs to happen when Entity is destroyed
    void Entity::onDestroy()
    {
        _alive = false;
    }

    void Entity::draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        target.draw(_sprite, states);
    }
}
