#pragma once
#include "../../ECS/World.h"

namespace cookie
{
	class DirectionalLightSystem : public System
	{
	public:
		virtual void Start(World* world) override;
		virtual void Update(World* world) override;
	};
}