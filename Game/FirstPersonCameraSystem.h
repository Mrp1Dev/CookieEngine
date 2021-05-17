#pragma once
#include "ECS/World.h"
#include <Rendering/CameraData.h>
#include <Rendering/TransformData.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class FirstPersonCameraSystem : public ck::System
{
public:
	virtual void Update(ck::World* world) override
	{
		auto cameraQuery { world->QueryEntities<ck::CameraData, ck::TransformData>() };
		auto* time { world->GetResource<ck::Time>() };
		auto* window { world->GetResource<ck::Window>() };
		constexpr float speed = 120.0f;
		constexpr float rotSpeed = 50.0f;
		cameraQuery->Foreach([&time, &window](ck::CameraData& camera, ck::TransformData& transform)
			{
				if (glfwGetKey(window->glfwWindow, GLFW_KEY_W) == GLFW_PRESS)
					transform.position += transform.rotation * glm::vec3(0, 0, 1) * speed * time->deltaTime;
				if (glfwGetKey(window->glfwWindow, GLFW_KEY_S) == GLFW_PRESS)
					transform.position += transform.rotation * glm::vec3(0, 0, -1) * speed * time->deltaTime;
				if (glfwGetKey(window->glfwWindow, GLFW_KEY_A) == GLFW_PRESS)
					transform.position += transform.rotation * glm::vec3(-1, 0, 0) * speed * time->deltaTime;
				if (glfwGetKey(window->glfwWindow, GLFW_KEY_D) == GLFW_PRESS)
					transform.position += transform.rotation * glm::vec3(1, 0, 0) * speed * time->deltaTime;
				if (glfwGetKey(window->glfwWindow, GLFW_KEY_UP) == GLFW_PRESS)
					transform.rotation =
					glm::rotate(
						transform.rotation, glm::radians(rotSpeed * time->deltaTime), glm::vec3(1, 0, 0)
					);
				if (glfwGetKey(window->glfwWindow, GLFW_KEY_DOWN) == GLFW_PRESS)
					transform.rotation =
					glm::rotate(
						transform.rotation, glm::radians(-rotSpeed * time->deltaTime), glm::vec3(1, 0, 0)
					);
				if (glfwGetKey(window->glfwWindow, GLFW_KEY_LEFT) == GLFW_PRESS)
					transform.rotation =
					glm::rotate(
						transform.rotation, glm::radians(-rotSpeed * time->deltaTime), glm::vec3(0, 1, 0)
					);
				if (glfwGetKey(window->glfwWindow, GLFW_KEY_RIGHT) == GLFW_PRESS)
					transform.rotation =
					glm::rotate(
						transform.rotation, glm::radians(rotSpeed * time->deltaTime), glm::vec3(0, 1, 0)
					);
				if (glfwGetKey(window->glfwWindow, GLFW_KEY_J) == GLFW_PRESS)
					transform.position += transform.rotation * glm::vec3(0, 1, 0) * speed * time->deltaTime;
				if (glfwGetKey(window->glfwWindow, GLFW_KEY_K) == GLFW_PRESS)
					transform.position += transform.rotation * glm::vec3(0, -1, 0) * speed * time->deltaTime;
			});
	}
};
