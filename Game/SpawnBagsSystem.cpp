#include "SpawnBagsSystem.h"
#include <Rendering/Lighting/PointLightData.h>
void SpawnBagsSystem::Start(ck::World* world)
{
    /*world->EnqueueEntitySpawn(
    ck::AssetManager::GetModel("backpack/backpack.obj", true),
    ck::AssetManager::GetShader("vertex_shader.glsl", "fragment_shader.glsl"),
    ck::TransformData {
    glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f), glm::fquat(glm::vec3(0, 0, 0))
    }
    );
    world->EnqueueEntitySpawn(
    ck::AssetManager::GetModel("backpack/backpack.obj", true),
    ck::AssetManager::GetShader("vertex_shader.glsl", "fragment_shader.glsl"),
    ck::TransformData {
    glm::vec3(0.0f, 2.0f, 0.0f), glm::vec3(1.0f), glm::fquat(glm::vec3(0, 45, 0))
    }
    );
    world->EnqueueEntitySpawn(
    ck::AssetManager::GetModel("untitled/untitled.obj", true),
    ck::AssetManager::GetShader("vertex_shader.glsl", "fragment_shader.glsl"),
    ck::TransformData {
    glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(1.0f), glm::fquat(glm::vec3(0, 90, 0))
    },
    ck::BaseColorData { glm::vec4(0.8f, 0.7f, 0.6f, 1.0f) }
    );*/
    auto model = ck::AssetManager::GetModel("Sponza-Master/sponza.obj", true);
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
            glm::vec3(0.0f, 100.0f, 0.0f),
            glm::vec3(1.0f),
            glm::fquat()
        },
        ck::PointLightData { glm::vec3(0.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 1.0f) }
    );
}
