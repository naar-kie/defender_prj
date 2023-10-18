/**
 * @file ResourceHandler.h
 *
 * Provides a generic handler for managing game resources.
 */
#ifndef RESOURCEHANDLER_H
#define RESOURCEHANDLER_H

#include <unordered_map>
#include <memory>

namespace defender
{
    /**
     * @class ResourceHandler
          * @brief Manages loading and access to game resources.
     * The ResourceHandler class provides a generic way to load and access various types of resources,
     * ensuring efficient memory management and easy resource retrieval.
     * @brief Provides a generic handler for managing game resources.
     * @tparam RESOURCE Type of the resource (e.g., sf::Texture, sf::Font).
     * @tparam IDENTIFIER Type representing unique identifiers for resources.
     */
    template<typename RESOURCE, typename IDENTIFIER = int>
    class ResourceHandler
    {
    public:
                // ... public member functions and variables ...

        /**
         * @brief Loads a resource from a file and associates it with an identifier.
         * @tparam Args Types of arguments needed for loading the resource.
         * @param id Unique identifier for the resource.
         * @param args Arguments needed for loading the resource.
         */

        /**
         * This c++11 feature lets us delete the copy constructor and operator,
         * which makes this class non-copyable.
         */
        ResourceHandler(const ResourceHandler &) = delete;
        ResourceHandler &operator=(const ResourceHandler &) = delete;

        ResourceHandler() = default;

        /**
         * This c++11 feature, variadic template, simply forwards any arguments to the
         * parent class without knowing them. This method uses it because not all SFML
         * resource classes use the same parameters.
         */
        template<typename ... Args>
        void load(const IDENTIFIER &id, Args &&... args)
        {
            std::unique_ptr<RESOURCE> ptr(new RESOURCE);
            if (!ptr->loadFromFile(std::forward<Args>(args)...))
                throw std::runtime_error("Impossible to load file");
            _map.emplace(id, std::move(ptr));
        }
        /**
         * @brief Gets the resource associated with the given identifier.
         * @param id Identifier of the resource.
         * @return Reference to the resource.
         */

        RESOURCE &get(const IDENTIFIER &id) const
        {
            return *_map.at(id);
        }

    private:
                // ... private member functions and variables ...

        std::unordered_map<IDENTIFIER, std::unique_ptr<RESOURCE>> _map;
    };
}

#endif
