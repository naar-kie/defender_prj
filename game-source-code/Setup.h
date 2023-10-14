#ifndef SETUP_H
#define SETUP_H

#include <SFML/Graphics.hpp>
#include "ResourceHandler.h"
#include "ActionMap.h"

namespace defender
{
    extern sf::Text _highScoreText;

    class Player;
    class Setup
    {
    public:
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
        static int lives;

        static void initialize();
        static void reset();

        static bool isGameOver();
        static void addScore(int s);
        static int getScore();

        static void draw(sf::RenderTarget &target);
        static int _score;


    private:
        static sf::Text _scoreText;
        static sf::Sprite _lifeSprite;

        static void initFonts();
        static void initTextures();

        static int _highScore;

        static void initPlayerInputs();
    };
}

#endif
