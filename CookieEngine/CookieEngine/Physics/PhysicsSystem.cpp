#include "PhysicsSystem.h"
#include <cassert>
#include <PhysicsComponents.h>
#include <Resources.h>
#include <RenderingComponents.h>
#include <ckMath.h>
namespace cookie
{
    namespace physics
    {
        namespace px = physx;
        using namespace math;
        void Physicssystem::Start(World* world)
        {
            foundation = PxCreateFoundation(PX_PHYSICS_VERSION, allocatorCallBack, errorCallBack);
            if (!foundation)
            {
                std::cout << "ERROR::PHYSX: Couldn't create foundation.\n";
                return;
            }
            constexpr bool recordMemoryAllocations { true };
            const auto scale = px::PxTolerancesScale();
            physics = PxCreatePhysics(PX_PHYSICS_VERSION, *foundation, scale, recordMemoryAllocations);
            if (!physics)
            {
                std::cout << "ERROR::PHYSX: Couldn't create physics.\n";
                return;
            }

            dispatcher = px::PxDefaultCpuDispatcherCreate(1);

            auto desc = px::PxSceneDesc(scale);
            desc.filterShader = px::PxDefaultSimulationFilterShader;
            desc.cpuDispatcher = dispatcher;
            desc.broadPhaseType = px::PxBroadPhaseType::eABP;
            scene = physics->createScene(desc);
            if (!scene)
            {
                std::cout << "ERROR::PHYSX: Couldn't create physics scene.\n";
                return;
            }

            pvd = px::PxCreatePvd(*foundation);

            cooking = PxCreateCooking(PX_PHYSICS_VERSION, *foundation, px::PxCookingParams(scale));
            if (!cooking)
            {
                std::cout << "ERROR::PHYSX: Couldn't create cooking.\n";
                return;
            }
            if (!PxInitExtensions(*physics, pvd))
            {
                std::cout << "ERROR::PHYSX: Couldn't init extensions.\n";
                return;
            }

        }
        void Physicssystem::FixedUpdate(World* world)
        {
            auto* time { world->GetResource<Time>() };
            auto* query { world->QueryEntities<BoxColliderData, TransformData, RigidbodyData>() };
            query->Foreach([&](BoxColliderData& collider, TransformData& transform, RigidbodyData& rb)
                {
                    if (!collider.initialized)
                    {
                        auto rbDynamic = physics->createRigidDynamic(px::PxTransform(transform.position, transform.rotation));
                        if (!rbDynamic) std::cout << "SSHIT RB DYNAMIC IS NULL\n";
                        auto geometry = px::PxBoxGeometry(collider.halfExtents);
                        geometry.isValid();
                        auto& rbRef = *rbDynamic;
                        px::PxShape* shape = physx::PxRigidActorExt::createExclusiveShape(rbRef, px::PxBoxGeometry(collider.halfExtents), *physics->createMaterial(0.5f, 0.5f, 0.1), px::PxShapeFlag::eSIMULATION_SHAPE);
                        rb.pxRbDynamic = rbDynamic;
                        scene->addActor(*rbDynamic);
                        collider.initialized = true;
                    }
                    auto pos = rb.pxRbDynamic->getGlobalPose().p;
                    auto rot = rb.pxRbDynamic->getGlobalPose().q;
                    std::cout << pos.x << ' ' << pos.y << ' ' << pos.z << '\n';
                    transform.position = pos;
                    transform.rotation = rot;
                    rb.pxRbDynamic->setLinearVelocity(rb.linearVelocity);
                });
            scene->simulate(time->fixedDeltaTime);
            scene->fetchResults(true);

        }
        void Physicssystem::Destroy(World* world)
        {
            scene->release();
            physics->release();
            cooking->release();
            pvd->release();
            foundation->release();
        }
    }
}