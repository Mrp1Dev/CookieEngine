#pragma once
#include <ckMath.h>

namespace cookie
{
    namespace physics
    {
        struct BoxColliderData
        {
            math::Vector3 extents { math::Vector3::One() };
            math::Vector3 offset { math::Vector3::Zero() };
        };
    }
}