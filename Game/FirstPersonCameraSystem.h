#pragma once
#include "ECS/World.h"
#include <Rendering/CameraData.h>
#include <Rendering/TransformData.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../CookieEngine/CookieEngine/Resources.h"

class FirstPersonCameraSystem : public ck::System
{
public:
	virtual void Update(ck::World* world) override
	{
		auto cameraQuery { world->QueryEntities<ck::CameraData, ck::TransformData>() };
		auto* time { world->GetResource<ck::Time>() };
		auto* window { world->GetResource<ck::Window>() };
		constexpr float speed = 150.0f;
		constexpr float rotSpeed = 50.0f;
		auto* input { world->GetResource<ck::Input>() };
		cameraQuery->Foreach([&time, &window, &input](ck::CameraData& camera, ck::TransformData& transform)
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
			});
	}
};
