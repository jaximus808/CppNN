#include <cmath>
#include <random>
#include <time.h>

float random(float _min, float _max)
{
    return (std::abs(sin(2000000.0 + time(NULL) * rand()))*(_max-_min))+(_min);
//     return ((abs(sin(1000000.0 + time(NULL) * rand())))+_min)*(_max);
}

/// Offers better random than rand() lul. First Parameter is min and second is max. If only one parameter inputted then parameter is max
float random(float _max)
{
    return (std::abs(sin(2000000.0 + time(NULL) * rand())))*_max;
}