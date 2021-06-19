#include <Cookie.h>
#include "SpawnLevelItemsSystem.h"
#include "FirstPersonCameraSystem.h"
#include <Math/Mathf.h>
#include <PhysicsComponents.h>
#include "CarControllerSystem.h"
void InitGame(ck::World* ecsWorld)
{
    ecsWorld->AddSystem(SpawnLevelItemsSystem {});
    ecsWorld->AddSystem(FirstPersonCameraSystem {});
    ecsWorld->AddSystem(CarControllerSystem{});
}
