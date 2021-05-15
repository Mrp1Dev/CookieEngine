#include "../CookieEngine/CookieEngine/Cookie.h"
#include "SpawnBagsSystem.h"

#include "FirstPersonCameraSystem.h"

void InitGame(ck::World* ecsWorld)
{
	ecsWorld->AddSystem(SpawnBagsSystem {}, false);
	ecsWorld->AddSystem(FirstPersonCameraSystem {}, false);
}
