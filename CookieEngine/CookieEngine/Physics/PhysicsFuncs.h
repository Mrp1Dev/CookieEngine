#pragma once
#include <RenderingComponents.h>
#include <Physics/BoxColliderData.h>
namespace cookie
{
    namespace physics
    {
        BoxColliderData GenBoxColliderDataFromBoundingBox(const math::BoundingBox& BB, const math::Vector3& extraExtents = math::Vector3::Zero(), const math::Vector3& extraOffset = math::Vector3::Zero(), const PhysicsMaterial& material = {}) noexcept;
    }
}