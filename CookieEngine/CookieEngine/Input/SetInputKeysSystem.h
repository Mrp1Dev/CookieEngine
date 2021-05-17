#pragma once
#include "../ECS/World.h"
#include <Input/Input.h>

namespace cookie
{
	class SetInputKeysSystem : public System
	{
	public:
		virtual void Update(World* world)
		{
			auto* input { world->GetResource<Input>() };
			for (auto keyCode : input->keyCodes)
			{
				auto& key = input->keys.at(keyCode);
				const auto& previousFramePressed = input->previousFramePressed.at(keyCode);
				key.pressed = input->currentlyPressed.at(keyCode);
				key.justPressed =
					(input->previousFramePressed.at(keyCode) == false && key.pressed);
				key.justUnpressed = 
					()
			}
		}
	};
}