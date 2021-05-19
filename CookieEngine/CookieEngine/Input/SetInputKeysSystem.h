#pragma once
#include "../ECS/World.h"
#include <Input/Input.h>
#include <ResourceTypes/Window.h>

namespace cookie
{
	class SetInputKeysSystem : public System
	{
	public:
		virtual void Update(World* world)
		{
			auto* input { world->GetResource<Input>() };
			auto* window { world->GetResource<Window>() };
			for (int i = 0; i < KEYS; i++)
			{
				KeyCode keyCode = static_cast<KeyCode>(i);
				auto& key = input->keys.at(keyCode);
				const auto& previousFramePressed = input->previousFramePressed.at(keyCode);
				key.pressed = 
					glfwGetKey(window->glfwWindow, (int)keyCode) == GLFW_PRESS;
				key.justPressed =
					(previousFramePressed == false && key.pressed == true);
				key.justUnpressed =
					(previousFramePressed == true && key.pressed == false);
				input->previousFramePressed.at(keyCode) = key.pressed;
			}
		}
	};
}