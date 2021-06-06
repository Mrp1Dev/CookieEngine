#pragma once
#include <ckMath.h>
namespace cookie
{
    struct TransformData
    {
        math::Vector3 position { math::Vector3::Zero() };
        math::Vector3 scale { math::Vector3::One() };
        math::Quaternion rotation { math::Quaternion::Identity() };
    };
}