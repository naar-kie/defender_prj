#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "../game-source-code/Action.h"
#include "../game-source-code/ActionMap.h"
#include "../game-source-code/ActionTarget.h"
#include "../game-source-code/Collision.h"
#include "../game-source-code/Enemy.h"
#include "../game-source-code/Entity.h"
#include "../game-source-code/Game.h"
#include "../game-source-code/Lander.h"
#include "../game-source-code/Player.h"
#include "../game-source-code/Pod.h"
#include "../game-source-code/ResourceHandler.h"
#include "../game-source-code/World.h"
#include "../game-source-code/Utilities.h"

#include <SFML/Graphics.hpp>
#include <vector>
using namespace defender;


//////////WORLD CLASS/////////////////
TEST_CASE("World creation") {
    defender::World world(800, 600);
    CHECK(world.getWidth() == 800);
    CHECK(world.getHeight() == 600);
    CHECK(world.size() == 0);
}
//________________________________________________//


//////////ACTION CLASS/////////////////
TEST_CASE("Action constructors and equality") {
    SUBCASE("Equality operator with an Event") {
        defender::Action action(sf::Keyboard::A, defender::Action::Type::Pressed);
        sf::Event event;
        event.type = sf::Event::KeyPressed;
        event.key.code = sf::Keyboard::A;

        CHECK(action == event); // The event matches the key and type set in the action
    }
}
//________________________________________________//


//////////RESOURCEHANDLER CLASS (Good Graphics Test - minor)/////////////////
TEST_CASE("ResourceHandler loading and retrieval (using Spaceship)") {
    defender::ResourceHandler<sf::Texture, int> textureHandler;
    textureHandler.load(1, "resources/Spaceship.png");

    SUBCASE("Check if this texture is loadedLoad a texture") {
        CHECK_NOTHROW(textureHandler.get(1));
    }

    SUBCASE("Retrieve a loaded texture by confirming it's size with required size") {
        sf::Texture& texture = textureHandler.get(1);
        CHECK(texture.getSize() == sf::Vector2u(64, 64));
    }

    SUBCASE("Retrieve a non-existing resource") {
        // Make sure trying to retrieve a non-existing resource throws an exception.
        CHECK_THROWS(textureHandler.get(2));
    }
}

TEST_CASE("Alien Missile loading and retrieval ") {
    defender::ResourceHandler<sf::Texture, int> textureHandler;
    textureHandler.load(1, "resources/AlienMissile.png");
    
    SUBCASE("Check if this texture is loadedLoad a texture") {
        CHECK_NOTHROW(textureHandler.get(1));
    }

    SUBCASE("Retrieve a loaded texture by confirming it's size with required size") {
        sf::Texture& texture = textureHandler.get(1);
        CHECK(texture.getSize() == sf::Vector2u(13, 54));
    }
}

TEST_CASE("Lander loading and retrieval ") {
    defender::ResourceHandler<sf::Texture, int> textureHandler;
    textureHandler.load(1, "resources/Enemy1.png");
    
    SUBCASE("Check if this texture is loadedLoad a texture") {
        CHECK_NOTHROW(textureHandler.get(1));
    }

    SUBCASE("Retrieve a loaded texture by confirming it's size with required size") {
        sf::Texture& texture = textureHandler.get(1);
        CHECK(texture.getSize() == sf::Vector2u(64, 64));
    }
}

TEST_CASE("Laser loading and retrieval ") {
    defender::ResourceHandler<sf::Texture, int> textureHandler;
    textureHandler.load(1, "resources/PlayerLaser.png");
    
    SUBCASE("Check if this texture is loadedLoad a texture") {
        CHECK_NOTHROW(textureHandler.get(1));
    }

    SUBCASE("Retrieve a loaded texture by confirming it's size with required size of Laser") {
        sf::Texture& texture = textureHandler.get(1);
        CHECK(texture.getSize() == sf::Vector2u(3, 32));
    }
}

TEST_CASE("Pod loading and retrieval ") {
    defender::ResourceHandler<sf::Texture, int> textureHandler;
    textureHandler.load(1, "resources/podAlien.png");
    
    SUBCASE("Check if this texture is loadedLoad a texture") {
        CHECK_NOTHROW(textureHandler.get(1));
    }

    SUBCASE("Retrieve a loaded texture by confirming it's size with required size of Pod") {
        sf::Texture& texture = textureHandler.get(1);
        CHECK(texture.getSize() == sf::Vector2u(99, 70));
    }
}

TEST_CASE("Swarmer loading and retrieval ") {
    defender::ResourceHandler<sf::Texture, int> textureHandler;
    textureHandler.load(1, "resources/swarmer.png");
    
    SUBCASE("Check if this texture is loadedLoad a texture") {
        CHECK_NOTHROW(textureHandler.get(1));
    }

    SUBCASE("Retrieve a loaded texture by confirming it's size with required size of Swarmer") {
        sf::Texture& texture = textureHandler.get(1);
        CHECK(texture.getSize() == sf::Vector2u(66, 66));
    }
}


//________________________________________________//


//////////UTILITIES CLASS/////////////////
TEST_CASE("Random number generation") {
    defender::Utilities::initialize();
    int randomInt = defender::Utilities::random(1, 10);
    CHECK(randomInt >= 1);
    CHECK(randomInt <= 10);

    float randomFloat = defender::Utilities::random(1.0f, 10.0f);
    CHECK(randomFloat >= 1.0f);
    CHECK(randomFloat <= 10.0f);
}
//________________________________________________//


//      ---Object Testing (Movement and Collision)---      //

//////////PLAYER CLASS (Spaceship)/////////////////
TEST_CASE("Player Movements")
{
    defender::Setup::initialize();
    defender::Game game;
    defender::Player player(*new defender::World(800, 600));
    player.setPosition(200,200);

        // sf::Keyboard::Key key = sf::Keyboard::A;
        // int type = defender::Action::Type::Pressed;
        // defender::Action action(key, type);

    SUBCASE("Move Up")
    {
        defender::Action action1(sf::Keyboard::Up, defender::Action::Type::Pressed);
        player.moveUp = true;
        player.movement.y -= player.shipSpeed;
        
        //player._actionMap
        //sf::Event event;
        //event.type = sf::Event::KeyPressed;
        //event.key.code = sf::Keyboard::Up;
        //defender::Setup::player->processEvent(event);
        
        player.processEvents();
        player.update(sf::seconds(0.1)); // Assuming a small time increment
        
        CHECK(player.getPosition().y < 200); // Check if player moved up (Y position decreased)
    }

    SUBCASE("Move Down")
    {
        player.moveDown = true;
        player.movement.y += player.shipSpeed;
        
        player.update(sf::seconds(0.1)); // Assuming a small time increment
        player.processEvents();
        CHECK(player.getPosition().y > 200); // Check if player moved down (Y position increased)
    }

    SUBCASE("Move Left")
    {
        player.moveLeft = true;
        player.movement.x -= player.shipSpeed;
        player.update(sf::seconds(0.1)); // Assuming a small time increment
       player.processEvents();
        CHECK(player.getPosition().x < 200); // Check if player moved left (X position decreased)
    }

    SUBCASE("Move Right")
    {
        sf::Vector2f initialPos= player.getPosition();
        player.moveRight = true;
        player.movement.x += player.shipSpeed;
        player.update(sf::seconds(0.1)); // Assuming a small time increment
        sf::Vector2f newPos= player.getPosition();
        CHECK(newPos.x > initialPos.x); // Check if player moved right (X position increased)
    }

    // NEED TO DO COLLITIONS TESTS
}
//________________________________________________//


//////////LANDER CLASS(Landers)/////////////////

//________________________________________________//


//////////SHOOT CLASS (Lasers and Missiles)/////////////////
TEST_CASE("Enemy Bullet Collide with Player"){
    Setup::initialize();
    Game game;
    Player player(*new World(800, 600));
    player.setPosition(200,200);

    Lander::newLander(*new World(800, 600));
    
}

//________________________________________________//

//////////POD CLASS(Pod and Swarmers)/////////////////

//________________________________________________//
