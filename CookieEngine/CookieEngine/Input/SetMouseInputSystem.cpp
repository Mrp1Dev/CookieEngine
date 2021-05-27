#include "SetMouseInputSystem.h"
#include <usings.h>
namespace cookie
{
	void SetMouseInputSystem::Update(World* world)
	{
		auto* input { world->GetResource<Input>() };
		auto* window { world->GetResource<Window>() };

		glfwSetInputMode(window->glfwWindow, GLFW_CURSOR,
			input->lockCursor ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);

		glm::dvec2 doubleMousePos {};
		glfwGetCursorPos(window->glfwWindow, &doubleMousePos.x, &doubleMousePos.y);
		input->mousePosition.x = scast<float>(doubleMousePos.x);
		input->mousePosition.y = scast<float>(doubleMousePos.y);
		input->mouseDelta = input->mousePosition - input->previousFramePos;
		input->previousFramePos = input->mousePosition;
	}
}