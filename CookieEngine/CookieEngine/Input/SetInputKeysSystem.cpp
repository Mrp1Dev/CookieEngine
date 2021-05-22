#include "SetInputKeysSystem.h"

namespace cookie
{
	void SetInputKeysSystem::Update(World* world)
	{
		auto* input { world->GetResource<Input>() };
		auto* window { world->GetResource<Window>() };
		for (int i = 0; i < KEYS; i++)
		{
			auto& key = input->keys.at(i);
			const auto& previousFramePressed = input->previousFramePressed.at(i);
			key.pressed =
				glfwGetKey(window->glfwWindow, GLFW_KEY_CODES.at(i)) == GLFW_PRESS;
			key.justPressed =
				(previousFramePressed == false && key.pressed == true);
			key.justUnpressed =
				(previousFramePressed == true && key.pressed == false);
			input->previousFramePressed.at(i) = key.pressed;
		}
	}
}