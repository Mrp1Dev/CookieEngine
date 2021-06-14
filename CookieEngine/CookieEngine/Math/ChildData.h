#pragma once
#include <ckMath.h>
#include <ECS/World.h>
namespace cookie
{
    struct ChildData
    {
        Entity parent; //MUST have a transform component
        math::Vector3 localPosition {};
        math::Quaternion localRotation { math::Quaternion::Identity() };
    };
}