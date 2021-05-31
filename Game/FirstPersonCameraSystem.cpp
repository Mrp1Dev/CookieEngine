#include "FirstPersonCameraSystem.h"
#include <algorithm>
#include <Math/Vector3.h>
using namespace ck;
using namespace ck::math;
void FirstPersonCameraSystem::Start(World* world)
{
    input = world->GetResource<Input>();
}

void FirstPersonCameraSystem::Update(World* world)
{
    auto cameraQuery { world->QueryEntities<CameraData, TransformData, FirstPersonControllerData>() };
    auto* time { world->GetResource<Time>() };
    auto* window { world->GetResource<Window>() };
    constexpr f32 speed = 500.0f;
    constexpr f32 rotSpeed = 50.0f;
    constexpr f32 mouseSenstivity = 0.002f;

    input->lockCursor = !input->keys[KeyCode::LeftAlt].pressed;
    cameraQuery->Foreach([&time, &window, this](
        CameraData& camera, TransformData& transform, FirstPersonControllerData& controller
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
                moveVector.Normalize();
                transform.position += moveVector * speed * time->deltaTime;
            }

            controller.xRot += input->mouseDelta.y * mouseSenstivity;
            controller.yRot += input->mouseDelta.x * mouseSenstivity;
            controller.xRot = std::clamp(controller.xRot, Mathf::Deg2Radf * -89.0f, Mathf::Deg2Radf * 89.0f);
            transform.rotation = Quaternion::Euler(controller.xRot, controller.yRot, 0.0f);
        });
}
