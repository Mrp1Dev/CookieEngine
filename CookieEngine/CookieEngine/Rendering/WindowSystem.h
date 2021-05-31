#pragma once
#include <Resources.h>
#include <ECS/World.h>
namespace cookie
{
    class WindowSystem : public System
    {
    public:
        void Update (World* world) override;
    };
}