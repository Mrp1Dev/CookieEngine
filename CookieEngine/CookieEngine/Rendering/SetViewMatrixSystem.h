#pragma once
#include "../ECS/World.h"
#include "TransformData.h"
#include "CameraData.h"
#include "ShaderData.h"

namespace cookie
{
	class SetViewMatrixSystem : public System
	{
	public:
		virtual void Update(World* world) override;
	};
}