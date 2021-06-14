#pragma once
#include <ECS/World.h>

namespace cookie
{
    class ChildCalculationSystem final : public System
    { 
    public:
        void Update(World* world) override;
    };
}