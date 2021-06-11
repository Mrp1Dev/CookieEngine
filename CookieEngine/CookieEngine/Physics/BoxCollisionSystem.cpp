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
        struct MinMax
        {
            f32 min;
            f32 max;
        };

        MinMax GetProjectionMinMax(const std::array<Vector3, 8>& vertices, const Vector3& axis)
        {
            auto min = Mathf::Abs(Vector3::Dot(vertices[0], axis));
            auto max = min;
            for (const auto& vert : vertices)
            {
                auto dot = Mathf::Abs(Vector3::Dot(vert, axis));
                min = Mathf::Min(dot, min);
                max = Mathf::Max(dot, min);
            }
            return { min, max };
        }

        bool DoesOverlap(MinMax A, MinMax B)
        {
            if (A.max < B.min) return false;
            if (A.min > B.max) return false;
            return true;
        }

        f32 GetOverlap(MinMax A, MinMax B)
        {
            if (!DoesOverlap(A, B)) return 0.0f;
            if (A.max < B.max)
            {
                return A.max - B.min;
            }
            return B.max - A.min;
        }
        
        bool MinMaxContains(const MinMax& a, const MinMax& b)
        {
            return 0 < 0; //todo
        }
       
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
                    auto sat = SAT(*colliders[i], *transforms[i], *colliders[j], *transforms[j]);
                    //transforms[j]->position -= sat;
                    std::cout << Mathf::Approximately(sat.SqrMagnitude(), 0.0f) << '\n';
                }
            }
        }

        Vector3 BoxCollisionSystem::SAT(BoxColliderData& colliderA, TransformData& transformA, BoxColliderData& colliderB, TransformData& transformB) const
        {
            const Vector3 Ea = transformA.rotation * colliderA.halfExtents;
            const Vector3 Eb = transformB.rotation * colliderB.halfExtents;
            const std::array<Vector3, 8> verticesA {
                transformA.position + Ea, //Top forward right
                transformA.position + -Ea, //bottom back left
                transformA.position + Vector3(Ea.x, -Ea.y, Ea.z), //bottom forward right
                transformA.position + Vector3(-Ea.x, Ea.y, Ea.z), //top forward left
                transformA.position + Vector3(-Ea.x, -Ea.y, Ea.z), //bottom left forward
                transformA.position + Vector3(-Ea.x, Ea.y, -Ea.z), //top left back
                transformA.position + Vector3(Ea.x, Ea.y, -Ea.z), //top right back
                transformA.position + Vector3(Ea.x, -Ea.y, -Ea.z), //bottom right back
            };
            const std::array<Vector3, 8> verticesB {
                transformB.position + Eb,
                transformB.position + -Eb,
                transformB.position + Vector3(Eb.x, -Eb.y, Eb.z),
                transformB.position + Vector3(-Eb.x, Eb.y, Eb.z),
                transformB.position + Vector3(-Eb.x, -Eb.y, Eb.z),
                transformB.position + Vector3(-Eb.x, Eb.y, -Eb.z),
                transformB.position + Vector3(Eb.x, Eb.y, -Eb.z),
                transformB.position + Vector3(Eb.x, -Eb.y, -Eb.z),
            };
            const Vector3 Ax = transformA.rotation * Vector3::Right();
            const Vector3 Ay = transformA.rotation * Vector3::Up();
            const Vector3 Az = transformA.rotation * Vector3::Forward();
            const Vector3 Bx = transformB.rotation * Vector3::Right();
            const Vector3 By = transformB.rotation * Vector3::Up();
            const Vector3 Bz = transformB.rotation * Vector3::Forward();
            //const SATData data { T, Ax, Ay, Az, Bx, By, Bz, Ea, Eb };
            const std::array<Vector3, 1> axes {
               Vector3::Right(),
                /*Vector3::Cross(Ax, Bx).Normalized(),
                Vector3::Cross(Ax, By).Normalized(),
                Vector3::Cross(Ax, Bz).Normalized(),
                Vector3::Cross(Ay, Bx).Normalized(),
                Vector3::Cross(Ay, By).Normalized(),
                Vector3::Cross(Ay, Bz).Normalized(),
                Vector3::Cross(Az, Bx).Normalized(),
                Vector3::Cross(Az, By).Normalized(),
                Vector3::Cross(Az, Bz).Normalized()*/
            };
            f32 smallestOverlap = std::numeric_limits<f32>::max();
            Vector3 smallestOverlapAxis {};
            for (auto& axis : axes)
            {
                MinMax projectionA = GetProjectionMinMax(verticesA, axis);
                MinMax projectionB = GetProjectionMinMax(verticesB, axis);
                if (!DoesOverlap(projectionA, projectionB)) return Vector3::Zero();
                f32 overlap = GetOverlap(projectionA, projectionB);
                if(overlap < smallestOverlap)
                {
                    smallestOverlap = overlap;
                    smallestOverlapAxis = axis;
                }
            }
            std::cout << "Smallest shit returned\n";
            return smallestOverlapAxis * smallestOverlap;
        }

        /*f32 BoxCollisionSystem::DAbs(const Vector3& a, const Vector3& b) const
        {
            return Mathf::Abs(Vector3::Dot(a, b));
        }
        bool BoxCollisionSystem::SATOnAxis(const std::array<Vector3, 8>& verticesA, const std::array<Vector3, 8>& verticesB, const Vector3& axis) const
        {
            return DAbs(data.T, L)
                > DAbs(data.Ax * data.Ea.x, L)
                + DAbs(data.Ay * data.Ea.y, L)
                + DAbs(data.Az * data.Ea.z, L)
                + DAbs(data.Bx * data.Eb.x, L)
                + DAbs(data.By * data.Eb.y, L)
                + DAbs(data.Bz * data.Eb.z, L);
            return AxisSA{}
        }*/
    }
}