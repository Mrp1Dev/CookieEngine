#include "BoxCollisionSystem.h"
#include <PhysicsComponents.h>
#include <RenderingComponents.h>
#include <ckMath.h>
#include <array>
namespace cookie
{
    namespace physics
    {
        int bleh = 3;
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

            for (u32 i = 0; i < colliderCount; i++)
            {
                for (u32 j = i + 1; j < colliderCount; j++)
                {
                    volatile bool bleh = SAT(*colliders[i], *transforms[i], *colliders[j], *transforms[j]);
                }
            }
        }

        bool BoxCollisionSystem::SAT(BoxColliderData& colliderA, TransformData& transformA, BoxColliderData& colliderB, TransformData& transformB) const
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
            const SATData data { T, Ax, Ay, Az, Bx, By, Bz, Ea, Eb };
            const std::array<Vector3, 15> axes {
                Ax,
                Ay,
                Az,
                Bx,
                By,
                Bz,
                Vector3::Cross(Ax, Bx),
                Vector3::Cross(Ax, By),
                Vector3::Cross(Ax, Bz),
                Vector3::Cross(Ay, Bx),
                Vector3::Cross(Ay, By),
                Vector3::Cross(Ay, Bz),
                Vector3::Cross(Az, Bx),
                Vector3::Cross(Az, By),
                Vector3::Cross(Az, Bz)
            };
            for (auto& axis : axes)
            {
                if (SATOnAxis(data, axis)) return false;
            }
            return true;
        }

        f32 BoxCollisionSystem::DAbs(const Vector3& a, const Vector3& b) const
        {
            return Mathf::Abs(Vector3::Dot(a, b));
        }

        bool BoxCollisionSystem::SATOnAxis(const SATData& data, const Vector3& L) const
        {
            return DAbs(data.T, L)
                > DAbs(data.Ax * data.Ea.x, L)
                + DAbs(data.Ay * data.Ea.y, L)
                + DAbs(data.Az * data.Ea.z, L)
                + DAbs(data.Bx * data.Eb.x, L)
                + DAbs(data.By * data.Eb.y, L)
                + DAbs(data.Bz * data.Eb.z, L);
        }

    }
}