#pragma once
#include <ECS/World.h>

namespace cookie
{
    class SetProjectionViewMatrices : public System
    {
    public:
        void Update(World* world) override;
        
    };
}