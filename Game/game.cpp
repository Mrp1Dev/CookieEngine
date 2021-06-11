#include "../CookieEngine/CookieEngine/Cookie.h"
#include "SpawnBagsSystem.h"

#include "FirstPersonCameraSystem.h"
#include <Math/Mathf.h>
#include <PhysicsComponents.h>
using namespace ck;
using namespace ck::physics;
using namespace ck::math;
void InitGame(World* ecsWorld)
{
	ecsWorld->EnqueueEntitySpawn(CameraData { 60.0f, true, 0.1f, 10000.0f },
		TransformData {
			Vector3(0.0f, 0.0f, 0.0f),
			Vector3(1.0f, 1.0f, 1.0f),
			Quaternion(Quaternion::Identity())
		},
		FirstPersonControllerData {},
		BoxColliderData {Vector3::Splat(0.5f)},
		RigidbodyData {}
		);
	ecsWorld->AddSystem(SpawnBagsSystem {}, false);
	ecsWorld->AddSystem(FirstPersonCameraSystem {}, false);
}
