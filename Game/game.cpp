#include "../CookieEngine/Cookie.h"
#include "SpawnBagsSystem.h"

void InitGame(ck::World* ecsWorld)
{
	ecsWorld->AddSystem(SpawnBagsSystem {}, false);
}
