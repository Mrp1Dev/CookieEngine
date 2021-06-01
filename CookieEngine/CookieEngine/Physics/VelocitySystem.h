#pragma once
#include <ECS/World.h>
namespace cookie
{
    namespace physics
    {
        class VelocitySystem : public System
        {
        public:
            void FixedUpdate(World* world) override;
        };
    }
}