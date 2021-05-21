#pragma once
#include "../ECS/World.h"
#include <Input/Input.h>
#include <ResourceTypes/Window.h>

namespace cookie
{
	class SetInputKeysSystem : public System
	{
	public:
		virtual void Update(World* world);
	};
}