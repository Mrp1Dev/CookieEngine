#include "SpawnLevelItemsSystem.h"
#include <Rendering/Lighting/PointLightData.h>
#include <PhysicsComponents.h>
#include "FirstPersonControllerData.h"
using namespace cookie;
using namespace cookie::math;
using namespace cookie::physics;
void SpawnLevelItemsSystem::Start(ck::World* world)
{

    /*auto model = ck::AssetManager::GetModel("Sponza-Master/sponza.obj", true);
    world->EnqueueEntitySpawn(
        model,
        ck::AssetManager::GetShader(ck::DefaultShaders::LIT_VERT, ck::DefaultShaders::LIT_FRAG),
        ck::TransformData {
            glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.05f), glm::fquat(glm::vec3(0, 0, 0))
        }
    );
    world->EnqueueEntitySpawn(
        model,
        ck::AssetManager::GetShader(ck::DefaultShaders::LIT_VERT, ck::DefaultShaders::LIT_FRAG),
        ck::TransformData {
            model.model->boundingBoxMax, glm::vec3(0.05f), glm::fquat(glm::vec3(0, 0, 0))
        }
    );

    world->EnqueueEntitySpawn(
        ck::TransformData {
            glm::vec3(0.0f, 5.0f, 0.0f),
            glm::vec3(1.0f),
            glm::fquat()
        },
        ck::PointLightData { glm::vec3(0.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 1.0f), 2.5f, 25.0f, 25.0f }
    );

    world->EnqueueEntitySpawn(
        ck::TransformData {
            glm::vec3(0.0f, 32.0f, 25.0f),
            glm::vec3(1.0f),
            glm::fquat()
        },
        ck::PointLightData { glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 1.0f), 3.0f, 25.0f, 25.0f }
    );*/
    //for (size_t i = 0; i < 1; i++)
    //    world->EnqueueEntitySpawn(AssetManager::GetModel("cube.obj", true),
    //        TransformData { Vector3(0.0f, 0.0f, 0.0f)},
    //        BoxColliderData {Vector3::One() * 0.5F}, AssetManager::GetShader(DefaultShaders::LIT_VERT, DefaultShaders::LIT_FRAG),
    //        BaseColorData { Vector3{0.8f, 1.0f, 1.0f} }
    //    );

    world->EnqueueEntitySpawn(CameraData { 60.0f, true, 0.1f, 10000.0f },
        TransformData {
            Vector3(0.0f, 2.0f, 0.0f),
            Vector3(1.0f, 1.0f, 1.0f),
            Quaternion(Quaternion::Identity())
        },
        FirstPersonControllerData { 5.0f, 20.0f },
        BoxColliderData { Vector3(1.0f, 2.0f, 1.0f) },
        RigidbodyData { RigidBodyMode::Dynamic }
    );

    /*world->EnqueueEntitySpawn(AssetManager::GetModel("cube.obj", true),
        TransformData { Vector3(0.0f, 0.0f, 0.0f), Vector3(100.0f, 2.0f, 100.0f) },
        BoxColliderData { Vector3::Splat(0.5f) },
        AssetManager::GetShader(DefaultShaders::LIT_VERT, DefaultShaders::LIT_FRAG),
        RigidbodyData { RigidBodyMode::Static },
        BaseColorData { Vector3{0.8f, 1.0f, 1.0f} }
    );*/

    world->EnqueueEntitySpawn(AssetManager::GetModel("cube.obj", true),
        TransformData { Vector3(0.0f, 0.0f, 10.0f), Vector3(1.0f, 3.0f, 10.0f) },
        BoxColliderData { Vector3::Splat(0.5f) },
        AssetManager::GetShader(DefaultShaders::LIT_VERT, DefaultShaders::LIT_FRAG),
        RigidbodyData { RigidBodyMode::Static },
        BaseColorData { Vector3{1.0f, 0.7f, 0.6f} }
    );

}
