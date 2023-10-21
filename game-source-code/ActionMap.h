/**
 * @file ActionMap.h
 *
 * Defines a mapping between game actions and corresponding events.
 */
#ifndef ACTIONMAP_H
#define ACTIONMAP_H

#include <unordered_map>
#include "Action.h"

namespace defender
{
     /**
     * @class ActionMap
     * @brief A mapping between game actions and corresponding events.
     * @tparam ActionID The type representing different game actions.
     */
/*
 * This is a template class so that KEY can be any type
 */
    template<typename T = int>
    class ActionMap
    {
    public:
        /**
         * This c++11 feature lets us delete the copy constructor and operator,
         * which makes this class non-copyable.
         */
        ActionMap(const ActionMap<T> &) = delete;
        ActionMap<T> &operator=(const ActionMap<T> &) = delete;
/**
         * @brief Bind a game action to an event handling function.
         * @param action The game action to bind.
         * @param function The event handling function.
         */
        ActionMap() = default;
        /**
         * @brief Handle an event based on the associated game action.
         * @param event The event to be handled.
         */

        // Getters and setters
        void map(const T &key, const Action &action);
        const Action &get(const T &key) const;
                // Unordered maps are faster at runtime
        std::unordered_map<T, Action> _map;

    private:

    };
}

#endif // class adapted from iZastic on 27/09/2023, Created on 11/8/2015.
