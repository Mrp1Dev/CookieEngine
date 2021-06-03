#pragma once
#include <ECS/World.h>

namespace cookie
{
    namespace physics
    {
        class BoxCollisionSystem : public System
        {
        public:
            void FixedUpdate(World* world) override;
        };
    }
}