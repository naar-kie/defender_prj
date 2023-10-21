/**
 * @file Setup.h
 *
 * Defines game setup configurations and resources.
 */
#ifndef SETUP_H
#define SETUP_H

#include <SFML/Graphics.hpp>
#include "ResourceHandler.h"
#include "ActionMap.h"

namespace defender
{
    /**
     * @class Setup
     * @brief Handles game setup configurations and resources.
     * The Setup class handles initialization, resource loading, player setup, and scoring mechanics.

     */
    extern sf::Text _highScoreText;

    class Player;
    class Setup
    {
    public:
        // ... public member functions and variables ...

        /**
         * @brief Initializes game resources and settings.
         */
        /**
         * This c++11 feature lets us delete the constructor, copy constructor and operator,
         * which makes this class non-copyable.
         */
        Setup() = delete;
        Setup(const Setup &) = delete;
        Setup &operator=(const Setup &) = delete;

        static void loadHighScore();
        static void saveHighScore();

        enum Fonts : int
        {
            Sansation
        };
        static ResourceHandler<sf::Font, int> fonts;

        enum Textures : int
        {
            Player,
            PlayerLife,
            ShootPlayer,
            lander,
            ShootLander,
            BigPod1,
            BigPod2,
            BigPod3,
            BigPod4,
            Swarmer1,
            Swarmer2,
            Swarmer3,
            Swarmer4,
        };
        static ResourceHandler<sf::Texture, int> textures;

        // Limit number of actions by storing them in an enum
        enum PlayerInputs : int
        {
            Up,
            Down,
            Left,
            Right,
            Shoot
        };
        static ActionMap<int> playerInputs;

        static defender::Player *player;
        static int level;
        static int swarmersKilled;
        static int lives;
        static int maxLanders;
        static int landersDestroyed;
 /**
         * @brief Initializes game resources and configurations.
         */
        static void initialize();
        /**
         * @brief Resets game variables to default values.
         */
        static void reset();
        static bool isGameOver();
        static bool isGameWon();
        /**
         * @brief Adds score to the player's total score.
         * @param s Score to be added.
         */
        static void addScore(int s);
        /**
         * @brief Gets the current player's score.
         * @return Current player's score.
         */
        static int getScore();
        /**
         * @brief Draws the player's score and remaining lives on the screen.
         * @param target Render target to draw on.
         */

        static void draw(sf::RenderTarget &target);
        static int _score;
        static int _highScore;
        // ... public member functions and variables ...

    private:
        static sf::Text _scoreText;
        static sf::Sprite _lifeSprite;

        /**
         * @brief Initializes font resources for the game.
         */
        static void initFonts();
        /**
         * @brief Initializes texture resources for the game.
         */
        static void initTextures();


        /**
         * @brief Initializes player input mappings for the game.
         */
        static void initPlayerInputs();
    };
}

#endif