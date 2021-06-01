#include "../CookieEngine/CookieEngine/Cookie.h"
#include "SpawnBagsSystem.h"

#include "FirstPersonCameraSystem.h"
#include <Math/Mathf.h>
#include <PhysicsComponents.h>
using namespace ck;

void InitGame(World* ecsWorld)
{
	ecsWorld->EnqueueEntitySpawn(CameraData { 60.0f, true, 0.1f, 10000.0f },
		TransformData {
			glm::vec3(0.0f, 100.0f, 0.0f),
			glm::vec3(1.0f, 1.0f, 1.0f),
			glm::fquat()
		},
		FirstPersonControllerData {},
		physics::VelocityData {}
		);
	ecsWorld->AddSystem(SpawnBagsSystem {}, false);
	ecsWorld->AddSystem(FirstPersonCameraSystem {}, false);
}
