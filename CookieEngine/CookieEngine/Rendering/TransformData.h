#pragma once
#include <Math/Math.h>
namespace cookie
{
    struct TransformData
    {
        math::Vector3 position { math::Vector3::Forward() };
        math::Vector3 scale { math::Vector3::One() };
        math::Quaternion rotation { math::Quaternion::Identity() };
    };
}