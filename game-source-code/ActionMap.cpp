#include "ActionMap.h"
#include <iostream>
#include <stdexcept>

namespace defender
{
    template<typename T>
    void ActionMap<T>::map(const T &key, const Action &action)
    {
        _map.emplace(key, action);
    }

    template<typename T>
    const Action &ActionMap<T>::get(const T &key) const
    {
        auto it = _map.find(key);
        return it->second;
    }

// Declaring a template type allows implementation to be in a separate (.cpp) file
    template class ActionMap<int>;
}
