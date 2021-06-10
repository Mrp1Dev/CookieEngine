#include "PhysicsSystem.h"
#include <cassert>
namespace cookie
{
    namespace physics
    {
        namespace px = physx;
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
            const bool bleh = desc.isValid();
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