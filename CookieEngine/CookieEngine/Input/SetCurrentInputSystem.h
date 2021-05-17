#pragma once
#include "../ECS/World.h"
#include <Input/Input.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <ResourceTypes/Window.h>

namespace cookie
{
	class SetCurrentInputSystem : public System
	{
	public:

		virtual void Update(World* world)
		{
			auto* input { world->GetResource<Input>() };
			auto* window { world->GetResource<Window>() };
			for (KeyCode code : input->keyCodes)
			{
				input->currentlyPressed.at(code) 
					= glfwGetKey(window->glfwWindow, (int)code) == GLFW_PRESS;
			}
		}
	};
}