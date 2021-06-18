#pragma once
#include <Usings.h>
namespace cookie
{
    namespace math
    {
        template<typename T>
        struct MinMax
        {
            T min;
            T max;

            MinMax(const T& min, const T& max) : min { min }, max { max }{}
        };

        using MinMaxf = MinMax<f32>;
    }
}