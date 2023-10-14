#include "ActionTarget.h"

namespace defender
{
    template<typename T>
    ActionTarget<T>::ActionTarget(const ActionMap<T> &map) : _actionMap(map)
    {
    }

    template<typename T>
    bool ActionTarget<T>::processEvent(const sf::Event &event) const
    {
        bool res = false;
        for (auto &pair : _eventsPoll)
        {
            if (_actionMap.get(pair.first) == event)
            {
                pair.second(event);
                res = true;
                break;
            }
        }
        return res;
    }

    template<typename T>
    void ActionTarget<T>::processEvents() const
    {
        for (auto &pair : _eventsRealTime)
        {
            const Action &action = _actionMap.get(pair.first);
            if (action.test())
                pair.second(action._event);
        }
    }

    template<typename T>
    void ActionTarget<T>::bind(const T &key, const FuncType &callback)
    {
        const Action &action = _actionMap.get(key);
        if (action._type & Action::Type::RealTime)
            _eventsRealTime.emplace_back(key, callback);
        else
            _eventsPoll.emplace_back(key, callback);
    }

    template<typename T>
    void ActionTarget<T>::unbind(const T &key)
    {
        // c++11 Lamba: [variables](parameters) -> return type
        auto remove_func = [&key](const std::pair<T, FuncType> &pair) -> bool {
            return pair.first == key;
        };

        const Action &action = _actionMap.get(key);
        if (action._type & Action::Type::RealTime)
            _eventsRealTime.remove_if(remove_func);
        else
            _eventsPoll.remove_if(remove_func);
    }

// Declaring a template type allows implementation to be in a separate (.cpp) file
    template class ActionTarget<int>;
}