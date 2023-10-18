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

namespace defender {
    // Simple manual mock for the World class
    class MockWorld : public World {
    public:
        MockWorld(int width, int height, sf::Vector2f initialPlayerPosition)
            : World(width, height) {
            // Create and add the player entity to the world with the initial position
            Player* player = new Player(*this);
            player->setPosition(initialPlayerPosition);
            add(player);
        }

        // Override the add method to provide mock behavior
        void add(Entity* entity)  {
            // Mock the add behavior here, e.g., store the entity for later inspection
            // You can add your custom behavior as needed for testing.
        }
    };
}

// TEST_CASE("Player movement up test") {
//     SUBCASE("Player moves up when 'Up' input is triggered") {
//         // Set the initial position for the player
//         sf::Vector2f initialPlayerPosition(400.0f, 500.0f);

//         // Create a mock world with the initial player position
//         defender::MockWorld world(800, 600, initialPlayerPosition);

//         // Create a Player instance with the mock world
//         defender::Player player(world);

//         // Simulate the "Up" input event
//         sf::Event upEvent;
//         upEvent.type = sf::Event::KeyPressed;
//         upEvent.key.code = sf::Keyboard::Up;

//         // Call the player's event handler to process the key press event
//         player.processEvents();

//         // Update the player's position (assuming a small time increment)
//         player.update(sf::seconds(0.1));  // Adjust delta time as needed

//         // Get the player's updated position
//         sf::Vector2f updatedPosition = player.getPosition();

//         // Check that the player has moved upwards (y-coordinate decreased)
//         CHECK(updatedPosition.y < 0.0);  // Adjust the expected position as needed
//     }
// }


using namespace defender;

TEST_CASE("Player Movements")
{
    defender::Setup::initialize();
    defender::Game game;
    //game.run();
    defender::Player player(*new defender::World(800, 600));
    player.setPosition(200,200);

    sf::Keyboard::Key key = sf::Keyboard::A;
        int type = defender::Action::Type::Pressed;
        defender::Action action(key, type);

    SUBCASE("Move Up")
    {
        defender::Action action1(sf::Keyboard::Up, defender::Action::Type::Pressed);
        // Simulate the 'Up' key press event
        sf::Event upKeyEvent;
        upKeyEvent.type = sf::Event::KeyPressed;
        upKeyEvent.key.code = sf::Keyboard::Up;
        player.processEvent(upKeyEvent);
        
        //player.moveUp = true;
        //player.movement.y -= player.shipSpeed;
        player.update(sf::seconds(0.1)); // Assuming a small time increment
        player.processEvents();
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
        player.moveRight = true;
        player.movement.x += player.shipSpeed;
        player.update(sf::seconds(0.1)); // Assuming a small time increment
        CHECK(player.getPosition().x > 200); // Check if player moved right (X position increased)
    }
}


//////////////////////

// TEST_CASE("Action constructors and equality") {
//     SUBCASE("Equality operator with an Event") {
//         defender::Action action(sf::Keyboard::A, defender::Action::Type::Pressed);
//         sf::Event event;
//         event.type = sf::Event::KeyPressed;
//         event.key.code = sf::Keyboard::A;

//         CHECK(action == event); // The event matches the key and type set in the action
//     }
// }


// ////////////////////////////////////

// TEST_CASE("ResourceHandler loading and retrieval") {
//     defender::ResourceHandler<sf::Texture, int> textureHandler;
//     textureHandler.load(1, "resources/Spaceship.png");
//     SUBCASE("Check if this texture is loadedLoad a texture") {
//         //textureHandler.load(1, "resources/Spaceship.png");
//         CHECK_NOTHROW(textureHandler.get(1));
//     }

//     SUBCASE("Retrieve a loaded texture by confirming it's size with required size") {
//         sf::Texture& texture = textureHandler.get(1);
//         CHECK(texture.getSize() == sf::Vector2u(64, 64));
//     }

//     SUBCASE("Retrieve a non-existing resource") {
//         // Make sure trying to retrieve a non-existing resource throws an exception.
//         CHECK_THROWS(textureHandler.get(2)); // Adjust this to your class's behavior.
//     }
// }