#include "CarControllerSystem.h"
#include <ckMath.h>
#include <Resources.h>
#include <PhysicsComponents.h>
#include <RenderingComponents.h>
#include "CarControllerData.h"

using namespace ck;
using namespace ck::math;
using namespace ck::physics;

void CarControllerSystem::FixedUpdate(World* world)
{
	auto input { world->GetResource<Input>() };
	auto time { world->GetResource<Time>() };
	auto carQuery { world->QueryEntities<TransformData, RigidbodyData, CarControllerData>() };
	carQuery->Foreach([&](TransformData& transform, RigidbodyData& rb, CarControllerData& car)
	{
		const auto FORWARD = Vector3::Left(); //I'm doing this because the car is tilted 90deg and ugh.
		f32 verticalDir { 0.0f };
		verticalDir += input->keys[KeyCode::UpArrow].pressed;
		verticalDir -= input->keys[KeyCode::DownArrow].pressed;
		rb.linearVelocity += transform.rotation * FORWARD * verticalDir * car.acceleration * time->fixedDeltaTime;
		rb.linearVelocity = Vector3::ClampMagnitude(rb.linearVelocity, car.maxSpeed);
		rb.linearVelocity += transform.rotation * -rb.linearVelocity * (Mathf::Approximately(verticalDir, 0.0f) ? 1.0f : 0.0f)  * car.drag * time->fixedDeltaTime;
	});
}