#pragma once
#include "../ECS/World.h"
#include "Input.h"
#include "../Resources.h"
namespace cookie
{
	class SetMouseInputSystem : public System
	{
	public:
		virtual void Update(World* world)
		{
			auto* input { world->GetResource<Input>() };
			auto* window { world->GetResource<Window>() };

			glfwSetInputMode(window->glfwWindow, GLFW_CURSOR,
				input->lockCursor ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);

			glm::dvec2 doubleMousePos {};
			glfwGetCursorPos(window->glfwWindow, &doubleMousePos.x, &doubleMousePos.y);
			input->mousePosition.x = static_cast<float>(doubleMousePos.x);
			input->mousePosition.y = static_cast<float>(doubleMousePos.y);
			input->mouseDelta = input->mousePosition - input->previousFramePos;
			input->previousFramePos = input->mousePosition;
		}
	};
}