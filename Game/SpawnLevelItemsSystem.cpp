#include "SpawnLevelItemsSystem.h"
#include <Rendering/Lighting/PointLightData.h>
#include <PhysicsComponents.h>
#include "FirstPersonControllerData.h"
#include "TurnSpeedData.h"
#include <Physics/PhysicsFuncs.h>
using namespace cookie;
using namespace cookie::math;
using namespace cookie::physics;
void SpawnLevelItemsSystem::Start(ck::World* world)
{
    world->QueryEntities<DirectionalLightData>()->Foreach([](DirectionalLightData& light)
        {
            light.color = Vector3::One();
            light.ambientColor = Vector3(0.75, 0.96, 1.0) * 0.3f;
        });
    auto bodyEntity = world->EnqueueEntitySpawn(
        TransformData { Vector3(0.0f, 0.0f, 0.0f) },
        FirstPersonControllerData { 10.0f, 2.0f },
        TurnSpeedData { 12.0f },
        BoxColliderData { Vector3(1.0f, 2.0f, 1.0f) },
        RigidbodyData { RigidBodyMode::Dynamic, PhysicsMaterial{1.0f, 1.0f, 0.0f} }
    );

    world->EnqueueEntitySpawn(
        CameraData { 60.0f, true, 0.1f, 10000.0f },
        TransformData {},
        TurnSpeedData { 12.0f },
        ChildData { bodyEntity, Vector3(0.0f, 2.0f, 0.0f) }
    );

    world->EnqueueEntitySpawn(
        TransformData { Vector3(44.0f, 12.0f, -44.0f), Vector3::Splat(0.1f) },
        AssetManager::GetShader(DefaultShaders::LIT_VERT, DefaultShaders::LIT_FRAG),
        AssetManager::GetModel("city/city.obj", true)
    );

    auto carModel { AssetManager::GetModel("cars/LowPolyCars.obj", true) };
    world->EnqueueEntitySpawn(
        TransformData { Vector3::Zero(), Vector3::Splat(2.0f) },
        AssetManager::GetShader(DefaultShaders::LIT_VERT, DefaultShaders::LIT_FRAG),
        carModel,
        physics::GenBoxColliderDataFromBoundingBox(BoundingBox(scast<Vector3>(carModel.model->boundingBoxMin), scast<Vector3>(carModel.model->boundingBoxMax)), Vector3::Zero(), Vector3::Zero()),
        RigidbodyData{RigidBodyMode::Static}
    );

    /*world->EnqueueEntitySpawn(AssetManager::GetModel("cube.obj", true),
        TransformData { Vector3(0.0f, 0.0f, 0.0f), Vector3(100.0f, 2.0f, 100.0f) },
        BoxColliderData { Vector3::Splat(1.0f) },
        AssetManager::GetShader(DefaultShaders::LIT_VERT, DefaultShaders::LIT_FRAG),
        RigidbodyData { RigidBodyMode::Static },
        BaseColorData { Vector3{0.8f, 1.0f, 1.0f} }
    );

    world->EnqueueEntitySpawn(AssetManager::GetModel("Ak_47/Ak-47.obj", true),
        TransformData {},
        AssetManager::GetShader(DefaultShaders::LIT_VERT, DefaultShaders::LIT_FRAG)
    );

    world->EnqueueEntitySpawn(AssetManager::GetModel("cube.obj", true),
        TransformData { Vector3(0.0f, 1.5f, 10.0f), Vector3(1.0f, 3.0f, 10.0f) },
        BoxColliderData { Vector3::Splat(1.0f) },
        AssetManager::GetShader(DefaultShaders::LIT_VERT, DefaultShaders::LIT_FRAG),
        RigidbodyData { RigidBodyMode::Static },
        BaseColorData { Vector3{1.0f, 0.7f, 0.6f} }
    );*/

}
