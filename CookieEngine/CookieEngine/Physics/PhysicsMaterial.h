#pragma once
#include <Usings.h>
namespace cookie
{
    namespace physics
    {
        struct PhysicsMaterial
        {
            f32 staticFriction { 0.0f };
            f32 dynamicFriction { 0.0f };
            f32 restitution { 0.0f };
        };
    }
}