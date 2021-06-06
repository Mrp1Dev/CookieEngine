#pragma once
#include <ECS/World.h>
#include <ckMath.h>
#include <PhysicsComponents.h>
#include <RenderingComponents.h>
#include <Usings.h>
namespace cookie
{
    namespace physics
    {
        class BoxCollisionSystem : public System
        {
            /*struct SATData
            {
                math::Vector3 T;
                math::Vector3 Ax;
                math::Vector3 Ay;
                math::Vector3 Az;
                math::Vector3 Bx;
                math::Vector3 By;
                math::Vector3 Bz;
                math::Vector3 Ea;
                math::Vector3 Eb;
            };*/
            //f32 DAbs(const math::Vector3& a, const math::Vector3& b) const;
            //bool SATOnAxis(const std::array<Vector3, 8>& verticesA, const std::array<Vector3, 8>& verticesB, const Vector3& L) const;
            math::Vector3 SAT(BoxColliderData& colliderA, TransformData& transformA, BoxColliderData& colliderB, TransformData& transformB) const;
        public:
            void FixedUpdate(World* world) override;
        };
    }
}