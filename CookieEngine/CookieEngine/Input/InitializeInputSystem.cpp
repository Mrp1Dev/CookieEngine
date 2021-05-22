#include "InitializeInputSystem.h"

namespace cookie
{
	void InitializeInputSystem::Start(World* world)
	{
		auto* input = world->AddResource<Input>({});
		input->keys.reserve(KEYS);
		for (int i = 0; i < KEYS; i++)
		{
			input->keys.push_back(Key(i));
		}
	}
}