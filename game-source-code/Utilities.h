#ifndef UTILITIES_H
#define UTILITIES_H

#include <cstdlib>
#include <ctime>

namespace defender
{
    class Utilities
    {
    public:
        static void initialize()
        {
            srand((unsigned int) time(NULL));
        }

        static int random(int min, int max)
        {
            return rand() % (max - min + 1) + min;
        }

        static float random(float min, float max)
        {
            return (rand() / float(RAND_MAX)) * (max - min) + min;
        }
    };
}

#endif 
