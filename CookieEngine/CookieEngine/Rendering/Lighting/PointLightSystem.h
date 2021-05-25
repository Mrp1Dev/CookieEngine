#pragma once
#include "ECS/World.h"
namespace cookie
{
    class PointLightSystem : public System
    {
    public:
        virtual void Update(World* world) override;
    };
}