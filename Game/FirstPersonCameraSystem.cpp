#include "FirstPersonCameraSystem.h"
#include <algorithm>
#include <Math/Vector3.h>
#include <PhysicsComponents.h>
using namespace ck;
using namespace ck::math;
using namespace ck::physics;

void FirstPersonCameraSystem::Update(World* world)
{
    constexpr f32 mouseDeltaReductionFactor = 1.0f / 10000.0f;
    auto query { world->QueryEntities <TransformData, FirstPersonControllerData,  CameraData>() };
    auto* input { world->GetResource<Input>() };
    query->Foreach([&](TransformData& transform, FirstPersonControllerData& controller,...)
        {
            auto localForward = transform.rotation * Vector3::Forward();
            auto xRot = Mathf::Clamp(input->mouseDelta.y * controller.turnSpeed * mouseDeltaReductionFactor, -Vector3::Angle(Vector3::Up(), localForward),Vector3::Angle(Vector3::Down(), localForward));
            auto yRot = input->mouseDelta.x *mouseDeltaReductionFactor * controller.turnSpeed;
            transform.rotation = Quaternion::Euler(0, yRot, 0) * transform.rotation;
            transform.rotation = transform.rotation * Quaternion::Euler(xRot, 0, 0);
        });
}

void FirstPersonCameraSystem::FixedUpdate(World* world)
{
    auto cameraQuery { world->QueryEntities<CameraData, RigidbodyData, TransformData, FirstPersonControllerData>() };
    auto* time { world->GetResource<Time>() };
    auto* window { world->GetResource<Window>() };
    auto* input { world->GetResource<Input>() };
    

    input->lockCursor = !input->keys[KeyCode::LeftAlt].pressed;
    cameraQuery->Foreach([&](
        CameraData& camera, RigidbodyData& rb, TransformData& transform, FirstPersonControllerData& controller
        )
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
                rb.linearVelocity = moveVector.Normalized() * controller.speed;
            }
            else rb.linearVelocity = Vector3::Zero();
        });
}
