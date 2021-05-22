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
	constexpr float speed = 150.0f;
	constexpr float rotSpeed = 50.0f;
	constexpr float mouseSenstivity = 0.002f;
	cameraQuery->Foreach([&time, &window, this](
		ck::CameraData& camera, ck::TransformData& transform, FirstPersonControllerData& controller
		)
		{
			auto localForward = transform.rotation * glm::vec3(0, 0, 1);
			localForward.y = transform.position.y;
			auto localRight = transform.rotation * glm::vec3(1, 0, 0);
			localRight.y = transform.position.y;
			if (input->keys.at(ck::KeyCode::W).pressed)
				transform.position += localForward * speed * time->deltaTime;
			if (input->keys.at(ck::KeyCode::S).pressed)
				transform.position += -localForward * speed * time->deltaTime;
			if (input->keys.at(ck::KeyCode::A).pressed)
				transform.position += -localRight * speed * time->deltaTime;
			if (input->keys.at(ck::KeyCode::D).pressed)
				transform.position += localRight * speed * time->deltaTime;
			
			controller.xRot += input->mouseDelta.y * mouseSenstivity;
			controller.yRot += input->mouseDelta.x * mouseSenstivity;
			controller.xRot = std::clamp(controller.xRot, glm::radians(-89.0f), glm::radians(89.0f));
			transform.rotation = glm::fquat(glm::vec3(controller.xRot, controller.yRot, 0));
		});
}
