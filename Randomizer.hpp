#pragma once
#include <cstdlib>
#include <ctime>

inline void RandomInit()// Randomizer
{
    srand(static_cast<unsigned>(time(nullptr)));
}

inline float RandomSpawnX(float min = 0.f, float max = 1920.f)// makes the entities spawn every where on the top of the screen
{
    return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}
