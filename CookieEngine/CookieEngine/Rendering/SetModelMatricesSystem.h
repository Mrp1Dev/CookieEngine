#pragma once
#include "../ECS/World.h"
#include "ShaderData.h"
#include "TransformData.h"
#include "ModelRendererData.h"
#include <glm/gtc/quaternion.hpp>

namespace cookie
{
	class SetModelMatricesSystem : public System
	{
	public:
		virtual void Update(World* world) override
		{
			auto query { world->QueryEntities<TransformData, ShaderData, ModelRendererData>() };
			query->Foreach([](TransformData& transform, ShaderData& shader, ModelRendererData& model)
				{
					if (model.enabled)
					{
						
					}
				});
		}
	};
}