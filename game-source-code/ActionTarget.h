/**
 * @file ActionTarget.h
 *
 * Defines the ActionTarget class template.
 */
#ifndef ACTIONTARGET_H
#define ACTIONTARGET_H

#include <SFML/Graphics.hpp>
#include "ActionMap.h"
#include <functional>
#include <list>

namespace defender
{
    /**
     * @class ActionTarget
     * @brief Provides a way to bind actions to specific functions.
     * @tparam ActionID Type representing unique identifiers for actions.
     */
    template<typename T = int>
    class ActionTarget
    {
    public:
        /**
         * @brief Function type representing actions.
         */
        /**
         * This c++11 feature lets us delete the copy constructor and operator,
         * which makes this class non-copyable.
         */
        ActionTarget(const ActionTarget<T> &) = delete;
        ActionTarget<T> &operator=(const ActionTarget<T> &) = delete;

        /**
         * This c++11 feature, using, defines the type of function that will be managed.
         * "using", is equivalent to typedef but more explicit
         */
        using FuncType = std::function<void(const sf::Event &event)>;
         /**
         * @brief Binds an action to a specific function.
         * @param action Action identifier to be bound.
         * @param function Function to be executed when the action occurs.
         */

        ActionTarget(const ActionMap<T> &map);

        /**
         * These methods are used to verify the internal events. The first for non real-time
         * events and the second for real-time events.
         */
         /**
         * @brief Processes the given event and executes corresponding functions.
         * @param event Event to be processed.
         */
        bool processEvent(const sf::Event &event) const;
        void processEvents() const;

        // This allows us to store actions and their functions in the appropriate list
        void bind(const T &key, const FuncType &callback);
        void unbind(const T &key);
        const ActionMap<T> &_actionMap;

    private:
        std::list<std::pair<T, FuncType>> _eventsRealTime;
        std::list<std::pair<T, FuncType>> _eventsPoll;


    };
}

#endif
