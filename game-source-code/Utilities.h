/**
 * @file Utilities.h
 *
 * Provides utility functions for the game.
 */
#ifndef UTILITIES_H
#define UTILITIES_H

#include <cstdlib>
#include <ctime>

namespace defender
{
     /**
     * @class Utilities
     * @brief Provides utility functions for the game.
     */
    class Utilities
    {
    public:
        /**
         * @brief Initializes the random number generator.
         */
        static void initialize()
        {
            srand((unsigned int) time(NULL));
        }
        /**
         * @brief Generates a random integer between min and max (inclusive).
         * @param min Minimum value of the random number.
         * @param max Maximum value of the random number.
         * @return Random integer between min and max.
         */

        static int random(int min, int max)
        {
            return rand() % (max - min + 1) + min;
        }
        /**
         * @brief Generates a random float between min and max.
         * @param min Minimum value of the random number.
         * @param max Maximum value of the random number.
         * @return Random float between min and max.
         */


        static float random(float min, float max)
        {
            return (rand() / float(RAND_MAX)) * (max - min) + min;
        }
    };
}

#endif
