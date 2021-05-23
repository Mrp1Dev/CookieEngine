#include "../CookieEngine/CookieEngine/Cookie.h"
#include "SpawnBagsSystem.h"

#include "FirstPersonCameraSystem.h"

void InitGame(ck::World* ecsWorld)
{
	ecsWorld->EnqueueEntitySpawn(ck::CameraData { 60.0f, true, 0.1f, 10000.0f },
		ck::TransformData {
			glm::vec3(0.0f, 100.0f, 0.0f),
			glm::vec3(1.0f, 1.0f, 1.0f),
			glm::fquat()
		},
		FirstPersonControllerData {});
	ecsWorld->AddSystem(SpawnBagsSystem {}, false);
	ecsWorld->AddSystem(FirstPersonCameraSystem {}, false);
}
