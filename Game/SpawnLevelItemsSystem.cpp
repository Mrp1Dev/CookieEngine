#include "SpawnLevelItemsSystem.h"
#include <Rendering/Lighting/PointLightData.h>
#include <PhysicsComponents.h>
#include <Physics/PhysicsFuncs.h>
#include "CarControllerData.h"
#include "CarFollowCameraData.h"
using namespace cookie;
using namespace cookie::math;
using namespace cookie::physics;
void SpawnLevelItemsSystem::Start(ck::World* world)
{
	SetUpDirLight(world);


	SpawnCity(world);

	auto car = SpawnCar(world);

	SpawnCamera(world, car);
}

void SpawnLevelItemsSystem::SpawnCamera(World* world, const Entity& car)
{
	world->EnqueueEntitySpawn(TransformData {}, CarFollowCameraData { car, Vector3(0.0f, 8.25f, -14.f), Quaternion::Euler(-12.0f, 0, 0) }, CameraData { 60.0f, true, 0.1f, 10000.0f });
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
	auto carModel { AssetManager::GetModel("cars/car.obj", true) };
	return world->EnqueueEntitySpawn(
		TransformData { Vector3(0, 5, 0), Vector3::Splat(2.5f) },
		AssetManager::GetShader(DefaultShaders::LIT_VERT, DefaultShaders::LIT_FRAG),
		carModel,
		physics::GenBoxColliderDataFromBoundingBox(BoundingBox(carModel.model->boundingBoxMin, carModel.model->boundingBoxMax), Vector3(1.f, 0.0f, 1.f), Vector3::Zero(), PhysicsMaterial { 0.0f, 0.0f, 0.0f }),
		PhysicsHandler::CreateRigidBodyDynamic(1.0, Vector3::Zero(), Vector3::Zero(), 0.0f, 3.0f),
		CarControllerData { 40.0f, 20.0f, 4.0f, 4.0f, 0.75f, 5.0f, 2.5f }
	);
}

void SpawnLevelItemsSystem::SpawnCity(World* world)
{
	auto model = AssetManager::GetModel("city/city.obj", true);
	auto collider = physics::GenBoxColliderDataFromBoundingBox({ model.model->boundingBoxMin, model.model->boundingBoxMax }, Vector3::Zero(), Vector3::Zero(), PhysicsMaterial { 0.0f, 0.0f, 0.0f });
	collider.extents.y = 1.0f;
	collider.offset.y = -120.0f;
	world->EnqueueEntitySpawn(
		TransformData { Vector3(44.0f, 12.0f, 44.0f), Vector3::Splat(0.1f) },
		AssetManager::GetShader(DefaultShaders::LIT_VERT, DefaultShaders::LIT_FRAG),
		model,
		collider,
		PhysicsHandler::CreateRigidBodyStatic()
	);

	world->EnqueueEntitySpawn(
		TransformData { Vector3(44.0f, 12.0f, 44.0f), Vector3::Splat(0.1f) },
		AssetManager::GetShader(DefaultShaders::LIT_VERT, DefaultShaders::LIT_FRAG),
		AssetManager::GetModel("city/city-collider-FINAL.obj", false),
		MeshColliderData {},
		PhysicsHandler::CreateRigidBodyStatic()
	);
}
