#include "Setup.h"
#include "Utilities.h"
#include "Player.h"
#include <fstream>

namespace defender
{
    ResourceHandler<sf::Font, int> Setup::fonts;
    ResourceHandler<sf::Texture, int> Setup::textures;

    ActionMap<int> Setup::playerInputs;
    int Setup::level;
    int Setup::maxLanders = 5;
    int Setup::lives;
    int Setup::swarmersKilled = 0;

    Player *Setup::player = nullptr;

    int Setup::_score;
    sf::Text Setup::_scoreText;

    int Setup::_highScore = 0;
    sf::Text _highScoreText;

    void Setup::initialize()
    {
        Utilities::initialize();
        initFonts();
        initTextures();
        initPlayerInputs();

        _scoreText.setFont(fonts.get(Fonts::Sansation));
        _scoreText.setCharacterSize(24);

        lives = level = _score = -1;

        _highScoreText.setFont(fonts.get(Fonts::Sansation));
        _highScoreText.setCharacterSize(24);
        _highScoreText.setString("High Score: " + std::to_string(_highScore));
        _highScoreText.setPosition(1050, 10);
    }

    void Setup::reset()
    {
        level = 1;
        lives = 0;
        _score = 0;
        swarmersKilled = 0;
        maxLanders = 5; // initialize maximum number of Landers
        _scoreText.setString("Score: 0");
    }

    bool Setup::isGameOver()
    {
        return lives < 0;
    }

    bool Setup::isGameWon()
    {
        return maxLanders == 0;
    }

    void Setup::addScore(int s)
    {
        int old = _score;
        _score += s * level;
        if (_score > _highScore) {
            _highScore = _score; // Update the high score if the current score is higher
        }
        lives += _score / 10000 - old / 10000;
        _scoreText.setString("Score: " + std::to_string(_score));
        _highScoreText.setString("High Score: " + std::to_string(_highScore));
    }

    int Setup::getScore()
    {
        return _score;
    }

    void Setup::draw(sf::RenderTarget &target)
    {
        target.draw(_scoreText);
        for (int i = 0; i < lives; ++i)
        target.draw(_highScoreText);
    }

    void Setup::initFonts()
    {
        fonts.load(Fonts::Sansation, "resources/sansation.ttf");
    }

    void Setup::initTextures()
    {
        textures.load(Textures::lander, "resources/Enemy1.png");
        textures.load(Textures::ShootLander, "resources/AlienMissile.png");

        textures.load(Textures::Player, "resources/Spaceship.png");
        textures.load(Textures::ShootPlayer, "resources/PlayerLaser.png");
        
        textures.load(Textures::BigPod1, "resources/podAlien.png");
        textures.load(Textures::BigPod2, "resources/podAlien.png");
        textures.load(Textures::BigPod3, "resources/podAlien.png");
        textures.load(Textures::BigPod4, "resources/podAlien.png");

        textures.load(Textures::Swarmer1, "resources/swarmer.png");
        textures.load(Textures::Swarmer2, "resources/swarmer.png");
        textures.load(Textures::Swarmer3, "resources/swarmer.png");
        textures.load(Textures::Swarmer4, "resources/swarmer.png");
    }

    void Setup::initPlayerInputs()
    {
        playerInputs.map(PlayerInputs::Up, Action(sf::Keyboard::Up));
        playerInputs.map(PlayerInputs::Down, Action(sf::Keyboard::Down));
        playerInputs.map(PlayerInputs::Right, Action(sf::Keyboard::Right));
        playerInputs.map(PlayerInputs::Left, Action(sf::Keyboard::Left));
        playerInputs.map(PlayerInputs::Shoot, Action(sf::Keyboard::Space));
    }
}