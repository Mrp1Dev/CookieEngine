#include "PhysicsFuncs.h"
namespace cookie
{
    namespace physics
    {
        using namespace math;
        BoxColliderData GenBoxColliderDataFromBoundingBox(const BoundingBox& BB, const Vector3& extraExtents, const Vector3& extraOffset) noexcept
        {
            Vector3 boxCenter = Vector3::Lerp(BB.min, BB.max, 0.5f);
            return BoxColliderData {
                (BB.max - BB.min) + extraExtents,
                boxCenter + extraOffset
            };
        }
    }
}