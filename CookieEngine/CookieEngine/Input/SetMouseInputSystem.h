#pragma once
#include "../ECS/World.h"
#include "Input.h"
#include "../Resources.h"
namespace cookie
{
	class SetMouseInputSystem : public System
	{
	public:
		virtual void Update(World* world);
	};
}