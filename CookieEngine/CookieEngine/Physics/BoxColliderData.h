#pragma once
#include <ckMath.h>
#include <PxPhysicsAPI.h>
namespace cookie
{
    namespace physics
    {
        struct BoxColliderData
        {
            math::Vector3 halfExtents { math::Vector3::One() * 0.5f };
            math::Vector3 offset { math::Vector3::Zero() };
        };
    }
}