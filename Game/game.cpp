#include "../CookieEngine/CookieEngine/Cookie.h"
#include "SpawnBagsSystem.h"

#include "FirstPersonCameraSystem.h"

void InitGame(ck::World* ecsWorld)
{
	ecsWorld->EnqueueEntitySpawn(ck::CameraData { 60.0f, true, 0.1f, 10000.0f }, ck::TransformData {}, FirstPersonControllerData {});
	ecsWorld->AddSystem(SpawnBagsSystem {}, false);
	ecsWorld->AddSystem(FirstPersonCameraSystem {}, false);
}
