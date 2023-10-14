#ifndef RESOURCEHANDLER_H
#define RESOURCEHANDLER_H

#include <unordered_map>
#include <memory>

namespace defender
{
    template<typename RESOURCE, typename IDENTIFIER = int>
    class ResourceHandler
    {
    public:
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

        RESOURCE &get(const IDENTIFIER &id) const
        {
            return *_map.at(id);
        }

    private:
        std::unordered_map<IDENTIFIER, std::unique_ptr<RESOURCE>> _map;
    };
}

#endif