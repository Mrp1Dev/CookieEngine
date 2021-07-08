#pragma once
#include <ECS/World.h>
#include <Rendering/TransformData.h>
#include <variant>
#include <PhysicsComponents.h>
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
            void InitializeRigidbody(World* world, std::variant<RigidBodyDynamicData*, RigidBodyStaticData*> rb, Entity entity, TransformData& transform);
        };
    }
}