#include "VelocitySystem.h"
#include "PhysicsComponents.h"
#include <RenderingComponents.h>
#include <ckMath.h>
#include <Resources.h>
namespace cookie
{
    namespace physics
    {
        using namespace math;
        void VelocitySystem::FixedUpdate(World* world)
        {
            auto query { world->QueryEntities<VelocityData, TransformData>() };
            auto* time { world->GetResource<Time>() };
            query->Foreach([&](VelocityData& velocity, TransformData& transform)
                {
                    transform.position += velocity.vel * time->fixedDeltaTime;
                });
        }
    }
}