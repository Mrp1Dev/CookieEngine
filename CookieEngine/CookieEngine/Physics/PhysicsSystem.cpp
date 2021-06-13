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
            auto scale = px::PxTolerancesScale();
            scale.length = 1;
            
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
            desc.gravity = Vector3(0.0f, -9.806f, 0.0f);
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
            auto* query { world->QueryEntities<TransformData, RigidbodyData>() };
            query->EntityForeach([&](Entity entity, TransformData& transform, RigidbodyData& rb)
                {
                    if (!rb.initialized)
                    {
                        px::PxRigidActor* rbActor { nullptr };
                        const auto pxTrans { px::PxTransform(transform.position, transform.rotation) };
                        if (rb.mode == RigidBodyMode::Dynamic)
                        {
                            rbActor = physics->createRigidDynamic(pxTrans);
                        }
                        else
                        {
                            rbActor = physics->createRigidStatic(pxTrans);
                        }
                        if (!rbActor) std::cout << "SSHIT RB DYNAMIC IS NULL\n";

                        auto collider = world->TryGetComponent<BoxColliderData>(entity);
                        if (collider.has_value())
                        {
                            px::PxShape* shape = physx::PxRigidActorExt::createExclusiveShape(
                                *rbActor,
                                px::PxBoxGeometry(collider.value()->halfExtents.ScaledBy(transform.scale)),
                                *physics->createMaterial(rb.physicsMaterial.staticFriction,
                                    rb.physicsMaterial.dynamicFriction, rb.physicsMaterial.restitution),
                                px::PxShapeFlag::eSIMULATION_SHAPE
                            );
                            rb.pxShape = shape;
                        }
                        rb.pxRbActor = rbActor;
                        scene->addActor(*rbActor);
                        rb.initialized = true;
                    }

                    auto pos = rb.pxRbActor->getGlobalPose().p;
                    rb.pxRbActor->setGlobalPose(px::PxTransform(pos, transform.rotation));
                    auto rot = rb.pxRbActor->getGlobalPose().q;
                    std::cout << pos.x << ' ' << pos.y << ' ' << pos.z << '\n';
                    transform.position = pos;
                    transform.rotation = rot;

                    if (rb.mode == RigidBodyMode::Dynamic)
                    {
                        scast<px::PxRigidDynamic*>(rb.pxRbActor)->setLinearVelocity(rb.linearVelocity);
                    }
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