#define _USE_MATH_DEFINES

#include "Player.h"
#include "Collision.h"
#include "Shoot.h"
#include "Utilities.h"
#include <cmath>

namespace defender
{
    // initializes the _sprite function, and delegate the job to the Entity constructor
    Player::Player(World &world) : Entity(Setup::Textures::Player, world),
                                   ActionTarget(Setup::playerInputs)
    {
        bind(Setup::PlayerInputs::Up, (const FuncType &) [this](const sf::Event &) {

            moveUp = true;
            movement.y -= shipSpeed;
        });

        bind(Setup::PlayerInputs::Down, (const FuncType &) [this](const sf::Event &) {
            moveDown = true;
            movement.y += shipSpeed;
        });

        bind(Setup::PlayerInputs::Left, (const FuncType &) [this](const sf::Event &) {
            facedLeft = true;
            moveLeft = true;
            if (facedRight)
            {
                _sprite.setRotation(270);
            }
            movement.x -= shipSpeed;
        });

        bind(Setup::PlayerInputs::Right, (const FuncType &) [this](const sf::Event &) {
            facedRight = true;
            moveRight = true;
            if (facedLeft)
            {
                _sprite.setRotation(90);
            }
            movement.x += shipSpeed;
        });

        bind(Setup::PlayerInputs::Shoot, (const FuncType &) [this](const sf::Event &) {
            shoot();
        });
    }

    // default behavior of the collision
    bool Player::isCollide(const Entity &other) const
    {
        return dynamic_cast<const ShootPlayer *>(&other) == nullptr && Collision::circleTest(_sprite, other._sprite);
    }

    void Player::processEvents()
    {
        ActionTarget::processEvents();
        //moveUp = 0, moveDown = 0, moveLeft = 0, moveRight = 0;
    }

    // function creates a ShootPlayer instance and adds it to the world
    void Player::shoot()
    {
        if (_timeSinceLastShoot > sf::seconds(0.3))
        {
            _world.add(new ShootPlayer(*this));
            _timeSinceLastShoot = sf::Time::Zero;
        }
    }


    // This method updates the position and the rotation of a Player
    void Player::update(sf::Time deltaTime)
    {
        float seconds = deltaTime.asSeconds();
        _timeSinceLastShoot += deltaTime;

        // Only move the ship if any movement keys are pressed
        if (moveUp || moveDown || moveLeft || moveRight)
        {
            _sprite.move(movement * deltaTime.asSeconds());
            moveUp = 0, moveDown = 0, moveLeft = 0, moveRight = 0;
        }
        movement.x = 0, movement.y = 0;
    }


    // this method ends the Game when the player dies
    void Player::onDestroy(){
        Entity::onDestroy();
        Setup::lives--;
        Setup::player = nullptr;
    }


    void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const{
        Entity::draw(target, states);
    }
}
