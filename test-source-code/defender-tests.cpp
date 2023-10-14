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

#include <SFML/Graphics.hpp>
#include <vector>
using namespace defender;

TEST_CASE("Player Movements")
{
    defender::Setup::initialize();
    defender::Player player(*new defender::World(800, 600));

    sf::Keyboard::Key key = sf::Keyboard::A;
        int type = defender::Action::Type::Pressed;
        defender::Action action(key, type);

    SUBCASE("Move Up")
    {
        defender::Action action1(sf::Keyboard::Up, defender::Action::Type::Pressed);
        player.moveUp = true;
        player.update(sf::seconds(0.1)); // Assuming a small time increment
        CHECK(player.getPosition().y < 0); // Check if player moved up (Y position decreased)
    }

    SUBCASE("Move Down")
    {
        player.moveDown = true;
        player.update(sf::seconds(0.1)); // Assuming a small time increment
        CHECK(player.getPosition().y > 0); // Check if player moved down (Y position increased)
    }

    SUBCASE("Move Left")
    {
        player.moveLeft = true;
        player.update(sf::seconds(0.1)); // Assuming a small time increment
        CHECK(player.getPosition().x < 0); // Check if player moved left (X position decreased)
    }

    SUBCASE("Move Right")
    {
        player.moveRight = true;
        player.update(sf::seconds(0.1)); // Assuming a small time increment
        CHECK(player.getPosition().x > 0); // Check if player moved right (X position increased)
    }
}

//////////////////////

TEST_CASE("Action constructors and equality") {
    SUBCASE("Equality operator with an Event") {
        defender::Action action(sf::Keyboard::A, defender::Action::Type::Pressed);
        sf::Event event;
        event.type = sf::Event::KeyPressed;
        event.key.code = sf::Keyboard::A;

        CHECK(action == event); // The event matches the key and type set in the action
    }
}


////////////////////////////////////

TEST_CASE("ResourceHandler loading and retrieval") {
    defender::ResourceHandler<sf::Texture, int> textureHandler;
    textureHandler.load(1, "resources/Spaceship.png");
    SUBCASE("Check if this texture is loadedLoad a texture") {
        //textureHandler.load(1, "resources/Spaceship.png");
        CHECK_NOTHROW(textureHandler.get(1));
    }

    SUBCASE("Retrieve a loaded texture by confirming it's size with required size") {
        sf::Texture& texture = textureHandler.get(1);
        CHECK(texture.getSize() == sf::Vector2u(64, 64));
    }

    SUBCASE("Retrieve a non-existing resource") {
        // Make sure trying to retrieve a non-existing resource throws an exception.
        CHECK_THROWS(textureHandler.get(2)); // Adjust this to your class's behavior.
    }
}