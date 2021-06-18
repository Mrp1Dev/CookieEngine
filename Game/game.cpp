#include "../CookieEngine/CookieEngine/Cookie.h"
#include "SpawnLevelItemsSystem.h"

#include "FirstPersonCameraSystem.h"
#include <Math/Mathf.h>
#include <PhysicsComponents.h>
#include <chrono>

using namespace ck;
using namespace ck::physics;
using namespace ck::math;
using namespace std::chrono;
void InitGame(World* ecsWorld)
{
    ecsWorld->AddSystem(SpawnLevelItemsSystem {}, false);
    ecsWorld->AddSystem(FirstPersonCameraSystem {}, false);

}
