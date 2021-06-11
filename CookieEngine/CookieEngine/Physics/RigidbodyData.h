#pragma once
#include <PxPhysicsAPI.h>
#include <ckMath.h>
namespace cookie
{
    namespace physics
    {
        struct RigidbodyData
        {
            physx::PxRigidDynamic* pxRbDynamic { nullptr };
            physx::PxShape* pxShape { nullptr };
            math::Vector3 linearVelocity { math::Vector3::Zero() };
        };

    }
}