#include "BoxCollisionSystem.h"
#include <PhysicsComponents.h>
#include <RenderingComponents.h>
#include <ckMath.h>
#include <array>
namespace cookie
{
    namespace physics
    {
        using namespace cookie::math;
        void BoxCollisionSystem::FixedUpdate(World* world)
        {
            std::vector<BoxColliderData*> colliders {};
            std::vector<TransformData*> transforms {};
            auto colliderQuery { world->QueryEntities<BoxColliderData, TransformData>() };
            const auto colliderCount = colliderQuery->Length();
            colliders.reserve(colliderCount);
            transforms.reserve(colliderCount);
            colliderQuery->Foreach([&](BoxColliderData& collider, TransformData& transform)
                {
                    colliders.push_back(&collider);
                    transforms.push_back(&transform);
                });
            const std::array<Vector3, 15> axes {
            };
            for (u32 i = 0; i < colliderCount; i++)
            {

            }
        }

        bool SAT(BoxColliderData& colliderA, TransformData& transformA, BoxColliderData& colliderB, TransformData& transformB)
        {
            
        }

        bool SATOnAxis(BoxColliderData& colliderA, TransformData& transformA, BoxColliderData& colliderB, TransformData& transformB, Vector3 axis)
        {
            const Vector3 T = transformB.position - transformA.position;
            const Vector3 Ax = transformA.rotation * Vector3::Right();
            const Vector3 Ay = transformA.rotation * Vector3::Up();
            const Vector3 Az = transformA.rotation * Vector3::Forward();
            const Vector3 Bx = transformB.rotation * Vector3::Right();
            const Vector3 By = transformB.rotation * Vector3::Up();
            const Vector3 Bz = transformB.rotation * Vector3::Forward();
            const Vector3 Ea = colliderA.extents;
            const Vector3 Eb = colliderB.extents;
            const Vector3 L = axis;
            return DAbs(T, L) > DAbs(Ax * Ea.x, L) + DAbs(Ay * Ea.y, L) + DAbs(Az * Ea.z, L) + DAbs(Bx * Eb.x, L) + DAbs(By * Eb.y, L) + DAbs(Bz * Eb.z, L);
        }

        f32 DAbs(const Vector3& a, const Vector3& b)
        {
            return Mathf::Abs(Vector3::Dot(a, b));
        }
    }
}