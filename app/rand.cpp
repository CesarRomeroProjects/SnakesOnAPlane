#include "rand.hpp"
#include <utility>
#include <cstdlib>

// Return a uniformly distributed random int from lowest to highest, inclusive
// This is an old-style random number generator;  we will see better ways 
// to generate random numbers later in the quarter. 
int randInt(int lowest, int highest)
{
    if (highest < lowest)
        std::swap(highest, lowest);
    return lowest + (rand() % (highest - lowest + 1));
}

