#include "FirstPersonCameraSystem.h"
#include <algorithm>

void FirstPersonCameraSystem::Start(ck::World* world)
{
	input = world->GetResource<ck::Input>();
	input->lockCursor = true;
}

void FirstPersonCameraSystem::Update(ck::World* world)
{
	auto cameraQuery { world->QueryEntities<ck::CameraData, ck::TransformData, FirstPersonControllerData>() };
	auto* time { world->GetResource<ck::Time>() };
	auto* window { world->GetResource<ck::Window>() };
	constexpr f32 speed = 500.0f;
	constexpr f32 rotSpeed = 50.0f;
	constexpr f32 mouseSenstivity = 0.002f;
	cameraQuery->Foreach([&time, &window, this](
		ck::CameraData& camera, ck::TransformData& transform, FirstPersonControllerData& controller
		)
		{
			glm::vec3 moveVector {};
			moveVector.z += input->keys[ck::KeyCode::W].pressed;
			moveVector.z -= input->keys[ck::KeyCode::S].pressed;
			moveVector.x += input->keys[ck::KeyCode::D].pressed;
			moveVector.x -= input->keys[ck::KeyCode::A].pressed;

			if (glm::length(moveVector) > 0.1f)
			{
				moveVector = transform.rotation * moveVector;
				//moveVector.y = 0;
				moveVector = glm::normalize(moveVector);
				transform.position += moveVector * speed * time->deltaTime;
			}

			controller.xRot += input->mouseDelta.y * mouseSenstivity;
			controller.yRot += input->mouseDelta.x * mouseSenstivity;
			controller.xRot = std::clamp(controller.xRot, glm::radians(-89.0f), glm::radians(89.0f));
			transform.rotation = glm::fquat(glm::vec3(controller.xRot, controller.yRot, 0));
		});
}
