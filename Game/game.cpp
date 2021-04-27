#include "../CookieEngine/CookieEngine/Cookie.h"
#include "SpawnBagsSystem.h"
#include <Rendering/SetViewMatrixSystem.h>
#include "FirstPersonCameraSystem.h"

void InitGame(ck::World* ecsWorld)
{
	ecsWorld->AddSystem(ck::SetViewMatrixSystem {}, false);
	ecsWorld->AddSystem(SpawnBagsSystem {}, false);
	ecsWorld->AddSystem(FirstPersonCameraSystem {}, false);
}
