#pragma once
#include "ECS/World.h"
#include <Rendering/CameraData.h>
#include <Rendering/TransformData.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../CookieEngine/CookieEngine/Resources.h"
#include "FirstPersonControllerData.h"

class FirstPersonCameraSystem : public ck::System
{
	ck::Input* input {};
public:
	virtual void Start(ck::World* world)
	{
		input = world->GetResource<ck::Input>();
		input->lockCursor = true;
	}
	virtual void Update(ck::World* world) override
	{
		auto cameraQuery { world->QueryEntities<ck::CameraData, ck::TransformData, FirstPersonControllerData>() };
		auto* time { world->GetResource<ck::Time>() };
		auto* window { world->GetResource<ck::Window>() };
		constexpr float speed = 150.0f;
		constexpr float rotSpeed = 50.0f;
		constexpr float mouseSenstivity = 0.05f;
		cameraQuery->Foreach([&time, &window, this](
			ck::CameraData& camera, ck::TransformData& transform, FirstPersonControllerData& controller
			)
			{
				if (input->keys.at(ck::KeyCode::W).pressed)
					transform.position += transform.rotation * glm::vec3(0, 0, 1) * speed * time->deltaTime;
				if (input->keys.at(ck::KeyCode::S).pressed)
					transform.position += transform.rotation * glm::vec3(0, 0, -1) * speed * time->deltaTime;
				if (input->keys.at(ck::KeyCode::A).pressed)
					transform.position += transform.rotation * glm::vec3(-1, 0, 0) * speed * time->deltaTime;
				if (input->keys.at(ck::KeyCode::D).pressed)
					transform.position += transform.rotation * glm::vec3(1, 0, 0) * speed * time->deltaTime;
				if (input->keys.at(ck::KeyCode::UpArrow).pressed)
					transform.rotation =
					glm::rotate(
						transform.rotation, glm::radians(rotSpeed * time->deltaTime), glm::vec3(1, 0, 0)
					);
				if (input->keys.at(ck::KeyCode::DownArrow).pressed)
					transform.rotation =
					glm::rotate(
						transform.rotation, glm::radians(-rotSpeed * time->deltaTime), glm::vec3(1, 0, 0)
					);
				if (input->keys.at(ck::KeyCode::LeftArrow).pressed)
					transform.rotation =
					glm::rotate(
						transform.rotation, glm::radians(-rotSpeed * time->deltaTime), glm::vec3(0, 1, 0)
					);
				if (input->keys.at(ck::KeyCode::RightArrow).pressed == GLFW_PRESS)
					transform.rotation =
					glm::rotate(
						transform.rotation, glm::radians(rotSpeed * time->deltaTime), glm::vec3(0, 1, 0)
					);
				if (input->keys.at(ck::KeyCode::J).pressed)
					transform.position += transform.rotation * glm::vec3(0, 1, 0) * speed * time->deltaTime;
				if (input->keys.at(ck::KeyCode::K).pressed)
					transform.position += transform.rotation * glm::vec3(0, -1, 0) * speed * time->deltaTime;

				controller.xRot += input->mouseDelta.y * time->deltaTime * mouseSenstivity;
				controller.yRot += input->mouseDelta.x * time->deltaTime * mouseSenstivity;
				controller.xRot = std::clamp(controller.xRot, glm::radians(-89.0f), glm::radians(89.0f));
				transform.rotation = glm::fquat(glm::vec3(controller.xRot, controller.yRot, 0));
			});
	}
};
