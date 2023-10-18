#include "Game.h"
#include "Pod.h"
#include "Lander.h"
#include "Player.h"
#include "Utilities.h"


namespace defender
{
    // initialize the window and the world
    Game::Game(unsigned int width, unsigned int height)
            : _window(sf::VideoMode(width, height), "Defender Game"), _world(width, height)
    {
        _text.setFont(Setup::fonts.get(Setup::Fonts::Sansation));
        _text.setCharacterSize(17);
        _text.setString("DEFENDER\n\nTo move the object use the up, down, left, and right arrows\nUse the space bar to shoot lasers\n"
                           "The landers appear as alien spaceship and will fire missiles at you. A pod will also appear as a larger alien ship to try and take you out the game"
                           "\nYou are able to shoot the landers and pods to take them out the game, however when shooting the pods they will release spawns"
                           "\nand colliding with them will end the game\n\n"
                           "\n\nIf either the pod or lander collides with you the game will end."
                           "\n\nYou are able to change the direction in which you shoot by using your left and right arrows.\n\nPress Enter to play or Esc to close game");
        sf::FloatRect size = _text.getGlobalBounds();
        _text.setOrigin(size.width / 2, size.height / 2);
        _text.setPosition(width / 2, height / 2);
        std::srand(static_cast<unsigned>(std::time(nullptr))); // Seed the random number generator
    }

    void Game::run(int minFPS) // run the game as quickly as possible by ensuring the time parameter passed in the Game::update() method is not too high
    {
        sf::Clock clock;
        sf::Time lastStep;
        sf::Time fixedStep = sf::seconds(1.f / minFPS); // fixed timeSteps for all events

        // Implements the "Minimum time step" model
        // Game runs as fast as it can, passing last delta to update()
        while (_window.isOpen())
        {
            processEvents(); 
            lastStep = clock.restart();
            while (lastStep > fixedStep)
            {
                lastStep -= fixedStep;
                update(fixedStep);
            }
            update(lastStep);
            render();
        }
    }

    void Game::initLevel(){
        Pod *Pod = new BigPod(_world);
        do
        {
            Pod->setPosition(Utilities::random(0.f, (float) _world.getWidth()),
                                Utilities::random(0.f, (float) _world.getHeight()));
        } while (_world.isCollide(*Pod));
        _world.add(Pod);
    }

    void Game::processEvents()
    {
        sf::Event event;
        while (_window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    _window.close();
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Escape)
                        _window.close();
                    if (Setup::isGameOver() && event.key.code == sf::Keyboard::Enter)
                        // DO FOR isGameWon();
                        reset();
                default:
                    break;
            }
            if (!Setup::isGameOver() && Setup::player != nullptr)
                Setup::player->processEvent(event);
        }
        if (!Setup::isGameOver() && Setup::player != nullptr)
            Setup::player->processEvents();
    }

    void Game::update(sf::Time deltaTime) // elapsed since the last call of Game.update
    {
        if (!Setup::isGameOver())
        {
            _world.update(deltaTime);

            if (Setup::player == nullptr)
            {
                Setup::player = new Player(_world);
                Setup::player->setPosition(_world.getWidth() / 2, _world.getHeight() / 2);
                _world.add(Setup::player);
            }
            _nextLander -= deltaTime;

            if (_nextLander < sf::Time::Zero && Setup::maxLanders > 0)
            {
                int sm = Setup::maxLanders;
                for (int i = 0; i < sm; ++i)
                {
                    Lander::newLander(_world);
                    Setup::maxLanders--;
                }
                Lander::newLander(_world);
                _nextLander = sf::seconds(Utilities::random(10.f, 60.f - Setup::level * 2));
            }

            if (_world.size() <= 1)
            {
                ++Setup::level;
    
                Setup::lives = -1;  // ~ use GameWon Splash Screen implementation
                initLevel();
            }
        }
    }

    void Game::render()
    {
        _window.clear();

        if (Setup::isGameOver())
            _window.draw(_text);
        else
        {
            _window.draw(_world);
            Setup::draw(_window);
        }

        _window.display();
    }

    void Game::reset()
    {
        _nextLander = sf::seconds(Utilities::random(5.f, 6.f - Setup::level * 2));
        _world.clear();
        Setup::player = nullptr;
        Setup::reset();
        initLevel();
    }
}
