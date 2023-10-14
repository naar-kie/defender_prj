#include "Action.h"
#include <cstring>

namespace defender
{
    Action::Action(const Action &other) : _type(other._type)
    {
        std::memcpy(&_event, &other._event, sizeof(sf::Event));
    }

    Action &Action::operator=(const Action &other)
    {
        std::memcpy(&_event, &other._event, sizeof(sf::Event));
        _type = other._type;
        return *this;
    }

    Action::Action(const sf::Keyboard::Key &key, int type) : _type(type)
    {
        _event.type = sf::Event::EventType::KeyPressed;
        _event.key.code = key;
    }

    bool Action::test() const
    {
        bool res = false;
        if (_event.type == sf::Event::EventType::KeyPressed) if (_type & Type::Pressed)
            res = sf::Keyboard::isKeyPressed(_event.key.code);
        return res;
    }

    bool Action::operator==(const sf::Event &event) const
    {
        bool res = false;
        switch (event.type)
        {
            case sf::Event::EventType::KeyPressed:
                if (_type & Type::Pressed && _event.type == sf::Event::EventType::KeyPressed)
                    res = event.key.code == _event.key.code;
                break;
            case sf::Event::EventType::KeyReleased:
                if (_type & Type::Released && _event.type == sf::Event::EventType::KeyPressed)
                    res = event.key.code == _event.key.code;
                break;
            default:
                break;
        }
        return res;
    }

    bool Action::operator==(const Action &other) const
    {
        return _type == other._type && other == _event;
    }
}