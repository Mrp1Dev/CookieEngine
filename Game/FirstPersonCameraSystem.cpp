#include "FirstPersonCameraSystem.h"
#include <algorithm>
#include <Math/Vector3.h>
#include <PhysicsComponents.h>
using namespace ck;
using namespace ck::math;
using namespace ck::physics;

void FirstPersonCameraSystem::Update(World* world)
{
    constexpr f32 rotSpeed = 50.0f;
    auto query { world->QueryEntities <TransformData, FirstPersonControllerData,  CameraData>() };
    auto* input { world->GetResource<Input>() };
    constexpr f32 mouseSenstivity = 0.001f;
    query->Foreach([&](TransformData& transform, ...)
        {
            auto localForward = transform.rotation * Vector3::Forward();
            auto xRot = Mathf::Clamp(input->mouseDelta.y * mouseSenstivity, -Vector3::Angle(Vector3::Up(), localForward),Vector3::Angle(Vector3::Down(), localForward));
            auto yRot = input->mouseDelta.x * mouseSenstivity;
            transform.rotation = Quaternion::Euler(0, yRot, 0) * transform.rotation;
            transform.rotation = transform.rotation * Quaternion::Euler(xRot, 0, 0);
        });
}

void FirstPersonCameraSystem::FixedUpdate(World* world)
{
    auto cameraQuery { world->QueryEntities<CameraData, VelocityData, TransformData, FirstPersonControllerData>() };
    auto* time { world->GetResource<Time>() };
    auto* window { world->GetResource<Window>() };
    auto* input { world->GetResource<Input>() };
    constexpr f32 speed = 1.0f;

    input->lockCursor = !input->keys[KeyCode::LeftAlt].pressed;
    cameraQuery->Foreach([&](
        CameraData& camera, VelocityData& velocity, TransformData& transform, ...
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
                moveVector.y = 0;
                velocity.vel = moveVector.Normalized() * speed;
            }
            else velocity.vel = Vector3::Zero();
        });
}
