#include <PxPhysicsAPI.h>
#include <ckMath.h>
#include <iostream>
#include <PhysicsComponents.h>
#include <Rendering/TransformData.h>
namespace cookie::physics::PhysicsHandler
{
	using namespace physx;
	using namespace math;
	
	PhysicsContext ctx = {};

	PxFilterFlags filterShader(
		PxFilterObjectAttributes attributes0,
		PxFilterData filterData0,
		PxFilterObjectAttributes attributes1,
		PxFilterData filterData1,
		PxPairFlags& pairFlags,
		const void* constantBlock,
		PxU32 constantBlockSize)
	{
		pairFlags |= PxPairFlag::eSOLVE_CONTACT;
		pairFlags |= PxPairFlag::eDETECT_DISCRETE_CONTACT;
		pairFlags |= PxPairFlag::eDETECT_CCD_CONTACT;
		return PxFilterFlags();
	}

	void SetupPhysics()
	{
		ctx.foundation = PxCreateFoundation(PX_PHYSICS_VERSION, ctx.allocatorCallback, ctx.errorCallBack);
		if (!ctx.foundation)
		{
			std::cout << "ERROR::PHYSX: Couldn't create ctx.foundation.\n";
			return;
		}
		constexpr bool recordMemoryAllocations { true };
		auto scale = PxTolerancesScale();
		//scale.length = 1;
		ctx.physics = PxCreatePhysics(PX_PHYSICS_VERSION, *ctx.foundation, scale, recordMemoryAllocations);
		if (!ctx.physics)
		{
			std::cout << "ERROR::PHYSX: Couldn't create ctx.physics.\n";
			return;
		}

		ctx.dispatcher = PxDefaultCpuDispatcherCreate(1);

		auto desc = PxSceneDesc(scale);
		desc.filterShader = filterShader;
		desc.cpuDispatcher = ctx.dispatcher;
	//	desc.broadPhaseType = PxBroadPhaseType::eABP;
		desc.flags |= PxSceneFlag::eENABLE_CCD;
		desc.gravity = Vector3(0.0f, -9.806f, 0.0f);
		ctx.scene = ctx.physics->createScene(desc);
		if (!ctx.scene)
		{
			std::cout << "ERROR::PHYSX: Couldn't create ctx.physics ctx.scene.\n";
			return;
		}

		ctx.pvd = PxCreatePvd(*ctx.foundation);

		ctx.cooking = PxCreateCooking(PX_PHYSICS_VERSION, *ctx.foundation, PxCookingParams(scale));
		if (!ctx.cooking)
		{
			std::cout << "ERROR::PHYSX: Couldn't create ctx.cooking.\n";
			return;
		}
		if (!PxInitExtensions(*ctx.physics, ctx.pvd))
		{
			std::cout << "ERROR::PHYSX: Couldn't init extensions.\n";
			return;
		}
	}

	RigidBodyDynamicData CreateRigidBodyDynamic(f32 mass, Vector3 linearVelcoity, Vector3 angularVelocity, f32 linearDamping, f32 angularDamping)
	{
		PxRigidDynamic* pxRb { nullptr };
		const auto pxTrans { PxTransform(Vector3::Zero(), Quaternion::Identity()) };
		pxRb = ctx.physics->createRigidDynamic(pxTrans);
		RigidBodyDynamicData rb {};
		rb.pxRb = pxRb;
		ctx.scene->addActor(*pxRb);
		pxRb->setMass(mass);
		pxRb->setLinearVelocity(linearVelcoity);
		pxRb->setAngularVelocity(angularVelocity);
		pxRb->setLinearDamping(linearDamping);
		pxRb->setAngularDamping(angularDamping);
		pxRb->setRigidBodyFlag(PxRigidBodyFlag::eENABLE_CCD, true);
		return rb;
	}

	RigidBodyStaticData CreateRigidBodyStatic()
	{
		PxRigidStatic* pxRb { nullptr };
		const auto pxTrans { PxTransform(Vector3::Zero(), Quaternion::Identity()) };
		pxRb = ctx.physics->createRigidStatic(pxTrans);
		RigidBodyStaticData rb {};
		rb.pxRb = pxRb;
		ctx.scene->addActor(*pxRb);
		return rb;
	}
}