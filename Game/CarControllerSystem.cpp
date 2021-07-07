#include "CarControllerSystem.h"
#include <ckMath.h>
#include <Resources.h>
#include <PhysicsComponents.h>
#include <RenderingComponents.h>
#include "CarControllerData.h"

using namespace ck;
using namespace ck::math;
using namespace ck::physics;
using namespace physx;
void CarControllerSystem::FixedUpdate(World* world)
{
	auto input { world->GetResource<Input>() };
	auto time { world->GetResource<Time>() };
	auto carQuery { world->QueryEntities<TransformData, RigidBodyDynamicData, CarControllerData, BoxColliderData>() };
	carQuery->Foreach([&](TransformData& transform, RigidBodyDynamicData& rb, CarControllerData& car, BoxColliderData& collider)
	{
        const auto VC = PxForceMode::eVELOCITY_CHANGE;

		//input
		f32 verticalAxis { 0.0f };
		verticalAxis += input->keys[KeyCode::UpArrow].pressed;
		verticalAxis -= input->keys[KeyCode::DownArrow].pressed;
		f32 horizontalAxis { 0.0f };
		horizontalAxis += input->keys[KeyCode::RightArrow].pressed;
		horizontalAxis -= input->keys[KeyCode::LeftArrow].pressed;
        rb.pxRb->setAngularDamping(3.0f);

        //Accel
        rb.pxRb->addForce(transform.rotation * Vector3::Forward() * car.acceleration * time->fixedDeltaTime * verticalAxis, VC);
        //Top speed clamp
        auto forwardVel = Vector3::Project(rb.pxRb->getLinearVelocity(), transform.rotation * Vector3::Forward());
//        rb.pxRb->addForce(forwardVel.Magnitude() > car.maxSpeed ? -(forwardVel - Vector3::ClampMagnitude(forwardVel, car.maxSpeed)) : Vector3::Zero(), VC);
        //De-accel
//        rb.pxRb->addForce(Vector3::Project(-rb.pxRb->getLinearVelocity(), transform.rotation * Vector3::Forward()) * car.slowdown * time->fixedDeltaTime * (Mathf::Approximately(verticalAxis, 0.0f) ? 1.0f : 0.0f), VC);
        //Sideways 'Drag'
 //       rb.pxRb->addForce(Vector3::Project(-rb.pxRb->getLinearVelocity(), transform.rotation * Vector3::Right()) * car.sidewaysDrag * time->fixedDeltaTime, VC);
        //Braking.
        if (!Mathf::Approximately(verticalAxis, 0.0f))
        {
            if (Vector3(rb.pxRb->getLinearVelocity()).Magnitude() > 0.0f)
            {
                auto dot = Vector3::Dot(Vector3(rb.pxRb->getLinearVelocity()).Normalized(), transform.rotation * Vector3::Forward());
                if ((dot > 0.0f && verticalAxis < 0.0f) || (dot < 0.0f && verticalAxis > 0.0f))
   //                 rb.pxRb->addForce(-rb.pxRb->getLinearVelocity() * car.brakingStrength * time->fixedDeltaTime * Mathf::Abs(verticalAxis), VC);
            }
        }
        //turning
        f32 carLength = collider.extents.z * transform.scale.z;
        auto actualTurnSpeed = car.turnSpeed * Mathf::InverseLerp(0.0f, carLength, forwardVel.Magnitude());
        auto td = Mathf::Sign(horizontalAxis) == Mathf::Sign(rb.pxRb->getAngularVelocity().y) ? Mathf::Clamp(actualTurnSpeed * time->fixedDeltaTime, 0.0f, Mathf::Max(car.maxTurnSpeed - Vector3(rb.pxRb->getAngularVelocity()).Magnitude(), 0.0f)) : actualTurnSpeed * time->fixedDeltaTime;
        rb.pxRb->addTorque(Vector3::Up() * horizontalAxis * td, VC);

	});
}