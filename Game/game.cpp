#include "../CookieEngine/CookieEngine/Cookie.h"
#include "SpawnLevelItemsSystem.h"

#include "FirstPersonCameraSystem.h"
#include <Math/Mathf.h>
#include <PhysicsComponents.h>
using namespace ck;
using namespace ck::physics;
using namespace ck::math;
void InitGame(World* ecsWorld)
{
    ecsWorld->AddSystem(SpawnLevelItemsSystem {}, false);
}
