#include "FirstPersonCameraSystem.h"
#include <algorithm>
#include <Math/Vector3.h>
#include <PhysicsComponents.h>
#include "TurnSpeedData.h"
using namespace ck;
using namespace ck::math;
using namespace ck::physics;

void FirstPersonCameraSystem::Update(World* world)
{
    constexpr f32 mouseDeltaReductionFactor = 1.0f / 10000.0f;
    auto cameraQuery { world->QueryEntities <TransformData, TurnSpeedData, CameraData>() };
    auto controllerQuery { world->QueryEntities<TransformData, TurnSpeedData, FirstPersonControllerData>() };
    auto* input { world->GetResource<Input>() };
    cameraQuery->Foreach([&](TransformData& transform, TurnSpeedData& turnSpeed ,...)
        {
            controllerQuery->Foreach([&](TransformData& transform, TurnSpeedData& turnSpeed, ...)
                {
                    transform.rotation = Quaternion::Euler(0, input->mouseDelta.x * turnSpeed.speed * mouseDeltaReductionFactor, 0) * transform.rotation;
                });

            auto localForward = transform.rotation * Vector3::Forward();
            transform.rotation = Quaternion::Euler(0, input->mouseDelta.x * turnSpeed.speed * mouseDeltaReductionFactor, 0) * transform.rotation;
            auto xRot = Mathf::Clamp(input->mouseDelta.y * turnSpeed.speed * mouseDeltaReductionFactor, -Vector3::Angle(Vector3::Up(), localForward),Vector3::Angle(Vector3::Down(), localForward));
            transform.rotation = transform.rotation * Quaternion::Euler(xRot, 0, 0);
        });
    
}

void FirstPersonCameraSystem::FixedUpdate(World* world)
{
    auto controllerQuery { world->QueryEntities<RigidbodyData, TransformData, FirstPersonControllerData>() };
    auto cameraQuery { world->QueryEntities<TransformData, CameraData>() };
    auto* time { world->GetResource<Time>() };
    auto* window { world->GetResource<Window>() };
    auto* input { world->GetResource<Input>() };
    

    input->lockCursor = !input->keys[KeyCode::LeftAlt].pressed;
    controllerQuery->Foreach([&](RigidbodyData& rb, TransformData& transform, FirstPersonControllerData& controller)
        {
            Vector3 moveVector { Vector3::Zero() };
            moveVector.z += input->keys[KeyCode::W].pressed;
            moveVector.z -= input->keys[KeyCode::S].pressed;
            moveVector.x += input->keys[KeyCode::D].pressed;
            moveVector.x -= input->keys[KeyCode::A].pressed;

            if (moveVector.SqrMagnitude() > 0.1f)
            {
                moveVector = transform.rotation * moveVector;
                //moveVector.y = 0;
                moveVector = moveVector.Normalized() * controller.speed;
                rb.linearVelocity = Vector3(moveVector.x, rb.linearVelocity.y, moveVector.z);
            }
            else rb.linearVelocity = Vector3::Zero();
            cameraQuery->Foreach([&](TransformData& camTransform, ...)
                {
                    camTransform.position = Vector3(transform.position.x, transform.position.y + controller.headHeight, transform.position.z);
                });
        });
}
