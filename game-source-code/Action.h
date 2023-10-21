#ifndef ACTION_H
#define ACTION_H

#include <SFML/Graphics.hpp>

namespace defender
{
    class Action
    {
    public:
        // Enum flags to be used by the constructors
        enum Type
        {
            RealTime = 1,
            Pressed = 1 << 1,
            Released = 1 << 2
        };

        /**
         * Copy constructor and operator copies the content of one Action
         * to the another. sf::Event does not contain pointers so std::memcpy
         * is used to copy other._event to this._event
         */
        Action(const Action &other);
        Action &operator=(const Action &other);

        /**
         * Multiple constructors allow a keyboard or mouse Action. Because a sf::Event.type
         * cannot be both Pressed and Release we store we that in _type and set the
         * sf::Event.type to Pressed.
         */
        Action(const sf::Keyboard::Key &key, int type = Type::RealTime | Type::Pressed);

        /**
         * @brief functionality to check if the internal sf::Event instance is executed.
         *
         * @return true if the instance has been executed
         * @return false otherwise
         */
        bool test() const; // functionality to check if the internal sf::Event instance is executed.

        /**
         * Because _event is always Pressed, this will compare Action._type to the flags
         * then return true if the key.code or button are correct
         */
        bool operator==(const sf::Event &event) const;
        // This compares the _type of each Action then calls the above function to compare events
        bool operator==(const Action &other) const;

    private:
        // friend, allows the named class to have access to this classes private variables
        template<typename T>
        friend class ActionTarget;

        // The sf::Event to be compared with and and _type to store the flags
        sf::Event _event;
        int _type;
    };
}

#endif
