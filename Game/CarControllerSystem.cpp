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
	auto carQuery { world->QueryEntities<TransformData, RigidbodyData, CarControllerData, BoxColliderData>() };
	carQuery->Foreach([&](TransformData& transform, RigidbodyData& rb, CarControllerData& car, BoxColliderData& collider)
	{
		const auto FORWARD = Vector3::Left(); //I'm doing this because the car is tilted 90deg and ugh.
		const auto RIGHT = Vector3::Forward();
		f32 verticalAxis { 0.0f };
		verticalAxis += input->keys[KeyCode::UpArrow].pressed;
		verticalAxis -= input->keys[KeyCode::DownArrow].pressed;
		f32 horizontalAxis { 0.0f };
		horizontalAxis += input->keys[KeyCode::RightArrow].pressed;
		horizontalAxis -= input->keys[KeyCode::LeftArrow].pressed;

		auto rotQuat = Quaternion::Euler(Vector3::Up() * horizontalAxis * car.turnSpeed * time->fixedDeltaTime);
		transform.rotation = rotQuat * transform.rotation; 
		rb.linearVelocity += transform.rotation * FORWARD * verticalAxis * car.acceleration * time->fixedDeltaTime;
		
		rb.linearVelocity = Vector3::ClampMagnitude(rb.linearVelocity, car.maxSpeed);
		f32 rightDot = Mathf::Abs(Vector3::Dot(rb.linearVelocity.Normalized(), transform.rotation * RIGHT));
		f32 drag = Mathf::Lerp(car.drag, car.sidewaysDrag, rightDot);
		f32 inputDragDiff = Mathf::Lerp(Mathf::Approximately(verticalAxis, 0.0f) ? 1.0f : 0.0f, 1.0f, rightDot);
		rb.linearVelocity +=
			-rb.linearVelocity
			* inputDragDiff
			* drag * time->fixedDeltaTime;
	});
}