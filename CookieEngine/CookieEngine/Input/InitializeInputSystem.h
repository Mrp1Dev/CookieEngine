#pragma once
#include "../ECS/World.h"
#include <Input/Input.h>

namespace cookie
{
	class InitializeInputSystem : System
	{
	public:
		virtual void Start(World* world)
		{
			auto* input = world->AddResource<Input>({});
			for (auto keyCode : input->keyCodes)
			{
				input->currentlyPressed.insert(std::pair { keyCode, false });
				input->previousFramePressed.insert(std::pair { keyCode, false });
				input->keys.insert(std::pair { keyCode, Key(keyCode) });
			}
		}
	};
}