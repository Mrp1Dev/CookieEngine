#pragma once
#include <PxPhysicsAPI.h>
#include <ckMath.h>
#include "RigidBodyMode.h"
#include "PhysicsMaterial.h"
namespace cookie
{
    namespace physics
    {
        struct RigidbodyData
        {
            RigidBodyMode mode { RigidBodyMode::Static };
            PhysicsMaterial physicsMaterial {};
            math::Vector3 linearVelocity { math::Vector3::Zero() };
            //The following does not need to be initalized in the initalizer list:
            physx::PxRigidActor* pxRbActor { nullptr };
            physx::PxShape* pxShape { nullptr };
            bool initialized { false };
        };

    }
}