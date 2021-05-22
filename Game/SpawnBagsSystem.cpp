#include "SpawnBagsSystem.h"
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
	world->EnqueueEntitySpawn(
		ck::AssetManager::GetModel("Sponza-Master/sponza.obj", true),
		ck::AssetManager::GetShader(ck::DefaultShaders::LIT_VERT, ck::DefaultShaders::LIT_FRAG),
		ck::TransformData {
			glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(1.0f), glm::fquat(glm::vec3(0, 0, 0))
		}
	);
}
