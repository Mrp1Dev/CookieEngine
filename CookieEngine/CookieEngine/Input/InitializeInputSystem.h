#pragma once
#include "../ECS/World.h"
#include <Input/Input.h>

namespace cookie
{
	class InitializeInputSystem : public System
	{
	public:
		virtual void Start(World* world)
		{
			auto* input = world->AddResource<Input>({});
			input->keys.reserve(KEYS);
			for (int i = 0; i < KEYS; i++)
			{
				input->keys.push_back(Key(i));
			}
		}
	};
}