#pragma once
#include <PxPhysicsAPI.h>
#include <Physics/RigidBodyDynamicData.h>
#include <Physics/RigidBodyStaticData.h>
#include <ckMath.h>
namespace cookie::physics::PhysicsHandler
{
	struct PhysicsContext
	{
		physx::PxDefaultErrorCallback errorCallBack;
		physx::PxDefaultAllocator allocatorCallback;
		physx::PxFoundation* foundation;
		physx::PxPvd* pvd;
		physx::PxPhysics* physics;
		physx::PxCooking* cooking;
		physx::PxScene* scene;
		physx::PxCpuDispatcher* dispatcher;
	};

	extern PhysicsContext ctx;

	void SetupPhysics();
	RigidBodyDynamicData CreateRigidBodyDynamic(f32 mass = 1.0f, math::Vector3 linearVelocity = math::Vector3::Zero(), math::Vector3 angularVelocity = math::Vector3::Zero(), f32 linearDamping = 0.0f, f32 angularDamping = 0.02f);
	RigidBodyStaticData CreateRigidBodyStatic();
}
