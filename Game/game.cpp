#include <Cookie.h>
#include "SpawnLevelItemsSystem.h"
#include "FirstPersonCameraSystem.h"
#include <Math/Mathf.h>
#include <PhysicsComponents.h>
#include "CarControllerSystem.h"
#include "CarCameraSystem.h"

void TestShit()
{
    auto rot = ck::math::Quaternion::RotationBetweenVectors(ck::math::Vector3::Forward(), ck::math::Vector3(0.0f, -0.4f, -1.0f).Normalized());
    assert(rot * ck::math::Vector3::Forward() == ck::math::Vector3(0.0f, -0.4f, -1.0f).Normalized());
}
void InitGame(ck::World* ecsWorld)
{
    TestShit();
    ecsWorld->AddSystem(SpawnLevelItemsSystem {});
    ecsWorld->AddSystem(FirstPersonCameraSystem {});
    ecsWorld->AddSystem(CarControllerSystem{});
    ecsWorld->AddSystem(CarCameraSystem {});
}
