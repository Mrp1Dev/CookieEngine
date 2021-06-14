#pragma once
#include <ECS/World.h>
#include <PxPhysicsAPI.h>
namespace cookie
{
    namespace physics
    {
        class PhysicsSystem final : public System
        {
            physx::PxDefaultErrorCallback errorCallBack;
            physx::PxDefaultAllocator allocatorCallBack;
            physx::PxFoundation* foundation;
            physx::PxPvd* pvd;
            physx::PxPhysics* physics;
            physx::PxCooking* cooking;
            physx::PxScene* scene;
            physx::PxCpuDispatcher* dispatcher;
        public:
            void Start(World* world) override;
            void FixedUpdate(World* world) override;
            void Destroy(World* world) override;
        };
    }
}