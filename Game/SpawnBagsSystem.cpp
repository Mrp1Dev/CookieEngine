#include "SpawnBagsSystem.h"
#include <Rendering/Lighting/PointLightData.h>
#include <PhysicsComponents.h>
using namespace cookie;
using namespace cookie::math;
using namespace cookie::physics;
void SpawnBagsSystem::Start(ck::World* world)
{

    /*auto model = ck::AssetManager::GetModel("Sponza-Master/sponza.obj", true);
    world->EnqueueEntitySpawn(
        model,
        ck::AssetManager::GetShader(ck::DefaultShaders::LIT_VERT, ck::DefaultShaders::LIT_FRAG),
        ck::TransformData {
            glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f), glm::fquat(glm::vec3(0, 0, 0))
        }
    );
    world->EnqueueEntitySpawn(
        model,
        ck::AssetManager::GetShader(ck::DefaultShaders::LIT_VERT, ck::DefaultShaders::LIT_FRAG),
        ck::TransformData {
            model.model->boundingBoxMax, glm::vec3(1.0f), glm::fquat(glm::vec3(0, 0, 0))
        }
    );

    world->EnqueueEntitySpawn(
        ck::TransformData {
            glm::vec3(0.0f, 50.0f, 0.0f),
            glm::vec3(1.0f),
            glm::fquat()
        },
        ck::PointLightData { glm::vec3(0.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 1.0f), 40.0f, 25.0f, 25.0f }
    );

    world->EnqueueEntitySpawn(
        ck::TransformData {
            glm::vec3(0.0f, 650.0f, 500.0f),
            glm::vec3(1.0f),
            glm::fquat()
        },
        ck::PointLightData { glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 1.0f), 40.0f, 25.0f, 25.0f }
    );*/
    for (size_t i = 0; i < 1; i++)
        world->EnqueueEntitySpawn(AssetManager::GetModel("cube.obj", true),
            TransformData { Vector3(0.0f, 0.0f, 0.0f)},
            BoxColliderData {Vector3::One() * 0.5F}, AssetManager::GetShader(DefaultShaders::LIT_VERT, DefaultShaders::LIT_FRAG),
            BaseColorData { Vector3{0.8f, 1.0f, 1.0f} }
        );

}
