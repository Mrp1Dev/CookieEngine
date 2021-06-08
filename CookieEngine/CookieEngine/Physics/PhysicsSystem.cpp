#include "PhysicsSystem.h"
namespace cookie
{
    namespace physics
    {
        void Physicssystem::Start(World* world)
        {
            foundation = PxCreateFoundation(PX_PHYSICS_VERSION, allocatorCallBack, errorCallBack);
            if (!foundation)
            {
                std::cout << "ERROR::PHYSX: Couldn't create foundation.\n";
                return;
            }
            constexpr bool recordMemoryAllocations { true };

            physics = PxCreatePhysics(PX_PHYSICS_VERSION, *foundation,
                physx::PxTolerancesScale(), recordMemoryAllocations);
            if (!physics)
            {
                std::cout << "ERROR::PHYSX: Couldn't create physics.\n";
                return;
            }

            pvd = physx::PxCreatePvd(*foundation);

            physx::PxTolerancesScale scale {};
            scale.length = 100;
            scale.length = 981;
            cooking = PxCreateCooking(PX_PHYSICS_VERSION, *foundation, physx::PxCookingParams(scale));
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
            scene = physics->createScene(physx::PxSceneDesc(scale));
            if (!scene)
            {
                std::cout << "ERROR::PHYSX: Couldn't create physics scene.\n";
                return;
            }
        }
        void Physicssystem::FixedUpdate(World* world)
        {
        }
        void Physicssystem::Destroy(World* world)
        {
            physics->release();
            cooking->release();
            pvd->release();
            foundation->release();
        }
    }
}