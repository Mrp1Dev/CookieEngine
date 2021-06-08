#pragma once
#include <ECS/World.h>
#include <PxPhysicsAPI.h>
namespace cookie
{
    namespace physics
    {
        class Physicssystem final : public System
        {
            physx::PxDefaultErrorCallback errorCallBack;
            physx::PxDefaultAllocator allocatorCallBack;
            physx::PxFoundation* foundation;
            physx::PxPvd* pvd;
            physx::PxPhysics* physics;
            physx::PxCooking* cooking;
            physx::PxScene* scene;
        public:
            void Start(World* world) override;
            void FixedUpdate(World* world) override;
            void Destroy(World* world) override;
        };
    }
}