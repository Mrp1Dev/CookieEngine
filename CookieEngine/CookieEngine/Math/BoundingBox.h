#pragma once
#include "MinMax.h"
namespace cookie
{

    namespace math
    {
        template<typename T>
        class Vector3T;

        template<typename T>
        using BoundingBoxT = MinMax<Vector3T<T>>;

        using BoundingBox = BoundingBoxT<f32>;
    }
}