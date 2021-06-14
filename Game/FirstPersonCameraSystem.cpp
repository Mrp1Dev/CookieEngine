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
    auto cameraQuery { world->QueryEntities <ChildData, TurnSpeedData, CameraData>() };
    auto controllerQuery { world->QueryEntities<TransformData, TurnSpeedData, FirstPersonControllerData>() };
    auto time { world->GetResource<Time>() };
    auto input { world->GetResource<Input>() };
    cameraQuery->Foreach([&](ChildData& transform, TurnSpeedData& turnSpeed ,...)
        {
            auto localForward = transform.localRotation * Vector3::Forward();
            auto xRot = Mathf::Clamp(input->mouseDelta.y * turnSpeed.speed * mouseDeltaReductionFactor, -Vector3::Angle(Vector3::Up(), localForward),Vector3::Angle(Vector3::Down(), localForward));
            transform.localRotation = transform.localRotation * Quaternion::Euler(xRot, 0, 0);
        });
    controllerQuery->Foreach([&](TransformData& transform, TurnSpeedData& turnSpeed, ...)
        {
            transform.rotation = Quaternion::Euler(0, input->mouseDelta.x * turnSpeed.speed * mouseDeltaReductionFactor, 0) * transform.rotation;
        });
    
}

void FirstPersonCameraSystem::FixedUpdate(World* world)
{
    auto controllerQuery { world->QueryEntities<RigidbodyData, TransformData, FirstPersonControllerData>() };
    auto cameraQuery { world->QueryEntities<ChildData, CameraData>() };
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
                moveVector = moveVector.Normalized() * controller.speed;
                rb.linearVelocity = Vector3(moveVector.x, rb.linearVelocity.y, moveVector.z);
            }
            else rb.linearVelocity = Vector3::Zero();
            cameraQuery->Foreach([&](ChildData& camTransform, ...)
                {
                    camTransform.localPosition = Vector3(0.0f, controller.headHeight, 0.0f);
                });
        });
}
