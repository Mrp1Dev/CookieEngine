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
        };

        using MinMaxf = MinMax<f32>;
    }
}