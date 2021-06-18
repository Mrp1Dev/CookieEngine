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
    auto time { world->GetResource<Time>() };
    auto input { world->GetResource<Input>() };
    cameraQuery->Foreach([&](TransformData& transform, TurnSpeedData& turnSpeed , CameraData& cam)
        {
            if (cam.parent.has_value())
            {
                auto localForward = transform.rotation * Vector3::Forward();
                auto xRot = Mathf::Clamp(input->mouseDelta.y * turnSpeed.speed * mouseDeltaReductionFactor, -Vector3::Angle(Vector3::Up(), localForward), Vector3::Angle(Vector3::Down(), localForward));
                transform.rotation = transform.rotation * Quaternion::Euler(xRot, 0, 0);
                transform.rotation = Quaternion::Euler(0, input->mouseDelta.x * turnSpeed.speed * mouseDeltaReductionFactor, 0) * transform.rotation;
            }
        });
    controllerQuery->Foreach([&](TransformData& transform, TurnSpeedData& turnSpeed, ...)
        {
            transform.rotation = Quaternion::Euler(0, input->mouseDelta.x * turnSpeed.speed * mouseDeltaReductionFactor, 0) * transform.rotation;
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
    controllerQuery->EntityForeach([&](Entity e, RigidbodyData& rb, TransformData& transform, FirstPersonControllerData& controller)
        {
            Vector3 moveVector { Vector3::Zero() };
            moveVector.z += input->keys[KeyCode::W].pressed;
            moveVector.z -= input->keys[KeyCode::S].pressed;
            moveVector.x += input->keys[KeyCode::D].pressed;
            moveVector.x -= input->keys[KeyCode::A].pressed;

            if (moveVector.SqrMagnitude() > 0.1f)
            {
                auto rot { Quaternion::Identity() };
                cameraQuery->Foreach([&](const TransformData& trans, CameraData& cam)
                    {
                        if (!cam.parent.has_value()) return;
                        if (cam.parent.value() == e) rot = trans.rotation;
                    });
                moveVector = rot * moveVector;
                //moveVector = transform.rotation * moveVector;
                moveVector = moveVector.Normalized() * controller.speed;
                rb.linearVelocity = moveVector;
            }
            else rb.linearVelocity = Vector3::Zero();
            
        });

    cameraQuery->Foreach([&](TransformData& camTransform, CameraData& cam)
        {
            if (cam.parent.has_value())
            {
                auto transform = world->TryGetComponent<TransformData>(cam.parent.value());
                if (!transform.has_value()) return;
                auto controller = world->TryGetComponent<FirstPersonControllerData>(cam.parent.value());
                if (!controller.has_value()) return;
                camTransform.position = transform.value()->position + Vector3::Up() * controller.value()->headHeight;
            }
        });
}
