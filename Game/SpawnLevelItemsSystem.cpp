#include "SpawnLevelItemsSystem.h"
#include <Rendering/Lighting/PointLightData.h>
#include <PhysicsComponents.h>
#include "FirstPersonControllerData.h"
#include "TurnSpeedData.h"
#include <Physics/PhysicsFuncs.h>
#include "CarControllerData.h"
#include "CarFollowCameraData.h"
using namespace cookie;
using namespace cookie::math;
using namespace cookie::physics;
void SpawnLevelItemsSystem::Start(ck::World* world)
{
	SetUpDirLight(world);

	//SpawnPlayer(world);

	SpawnCity(world);

	auto car = SpawnCar(world);

	SpawnCamera(world, car);
}

void SpawnLevelItemsSystem::SpawnCamera(World* world, const Entity& car)
{
	world->EnqueueEntitySpawn(TransformData {}, CarFollowCameraData { car, Vector3(10.0f, 4.75f, 0.0f), Quaternion::Euler(-12.0f, 0, 0) }, CameraData { 60.0f, true, 0.1f, 10000.0f });
}

void SpawnLevelItemsSystem::SetUpDirLight(cookie::World* world)
{
	world
		->QueryEntities<DirectionalLightData>()
		->Foreach([](DirectionalLightData& light)
	{
		light.color = Vector3::One();
		light.ambientColor = Vector3(0.75, 0.96, 1.0) * 0.3f;
	});
}

Entity SpawnLevelItemsSystem::SpawnCar(World* world)
{
	auto carModel { AssetManager::GetModel("cars/LowPolyCars.obj", true) };
	return world->EnqueueEntitySpawn(
		TransformData { Vector3::Zero(), Vector3::Splat(2.5f) },
		AssetManager::GetShader(DefaultShaders::LIT_VERT, DefaultShaders::LIT_FRAG),
		carModel,
		physics::GenBoxColliderDataFromBoundingBox(BoundingBox(carModel.model->boundingBoxMin, carModel.model->boundingBoxMax), Vector3::Zero(), Vector3::Zero()),
		RigidbodyData { RigidBodyMode::Dynamic, 100.0f },
		CarControllerData { 50.0f, 25.0f, 0.6f, 1.0f, 10.0f, 2.0f }
	);
}

void SpawnLevelItemsSystem::SpawnCity(World* world)
{
	auto model = AssetManager::GetModel("city/city.obj", true);
	auto collider = physics::GenBoxColliderDataFromBoundingBox({ model.model->boundingBoxMin, model.model->boundingBoxMax });
	collider.extents.y = 1.0f;
	collider.offset.y = -120.0f;
	world->EnqueueEntitySpawn(
		TransformData { Vector3(44.0f, 12.0f, -44.0f), Vector3::Splat(0.1f) },
		AssetManager::GetShader(DefaultShaders::LIT_VERT, DefaultShaders::LIT_FRAG),
		model,
		collider,
		RigidbodyData { RigidBodyMode::Static }
	);
}

void SpawnLevelItemsSystem::SpawnPlayer(World* world)
{
	auto bodyEntity = world->EnqueueEntitySpawn(
		TransformData { Vector3(0.0f, 3.0f, 0.0f) },
		FirstPersonControllerData { 25.0f, 0.0f },
		TurnSpeedData { 12.0f },
		BoxColliderData { Vector3(1.0f, 1.0f, 1.0f) },
		RigidbodyData { RigidBodyMode::Dynamic, 1.0f, PhysicsMaterial{1.0f, 1.0f, 0.0f} }
	);

	world->EnqueueEntitySpawn(
		CameraData { 60.0f, true, 0.1f, 10000.0f, bodyEntity },
		TransformData {},
		TurnSpeedData { 12.0f }
	);
}
