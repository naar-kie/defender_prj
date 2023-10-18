/**
 * @file Player.h
 *
 * Defines the player class for the game.
 */
#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "ActionTarget.h"
#include "Entity.h"
#include "World.h"

namespace defender
{
    class Player : public Entity, public ActionTarget<int>
    {
        /**
     * @class Player
     * @brief Represents the player entity in the game.
     */
    public:
                // ... public member functions and variables ...

        /**
         * @brief Constructor for Player class.
         * @param world Reference to the game world.
         */

        /**
         * This c++11 feature lets us delete the copy constructor and operator,
         * which makes this class non-copyable. Only want one player.
         */
        Player(const Player &) = delete;
        Player &operator=(const Player &) = delete;

        Player(World &world);
        /**
         * @brief Updates the player's position and rotation based on input.
         * @param deltaTime Time passed since the last update.
         */

        virtual bool isCollide(const Entity &other) const;
        /**
         * @brief Updates the position and rotation of the player character.
         * @param deltaTime Time passed since the last update.
         */
        virtual void update(sf::Time deltaTime);
        /**
         * @brief Processes player input events.
         */
        virtual void onDestroy();

        void processEvents();
        /**
         * @brief Handles shooting functionality for the player.
         */
        void shoot();

        bool moveUp = 0, moveDown = 0, moveLeft = 0, moveRight = 0; // mine

        sf::Vector2f movement;
        float shipSpeed = 350.f;


    private:
         /**< Speed of the player's ship. */
        int _rotation;
        int direction;
        bool facedRight = true;
        bool facedLeft = false;
        sf::Time _timeSinceLastShoot;
        

        /**
         * @brief Draws the player character on the render target.
         * @param target Render target to draw on.
         * @param states Current render states.
         */
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    };
}

#endif
