#pragma once
#include <ECS/World.h>
#include <PxPhysicsAPI.h>
namespace cookie
{
    namespace physics
    {
        class PhysicsSystem final : public System
        {
        public:
            void Start(World* world) override;
            void FixedUpdate(World* world) override;
            void Destroy(World* world) override;
        };
    }
}