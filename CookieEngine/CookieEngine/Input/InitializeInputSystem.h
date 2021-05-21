#pragma once
#include "../ECS/World.h"
#include <Input/Input.h>

namespace cookie
{
	class InitializeInputSystem : public System
	{
	public:
		virtual void Start(World* world);
	};
}