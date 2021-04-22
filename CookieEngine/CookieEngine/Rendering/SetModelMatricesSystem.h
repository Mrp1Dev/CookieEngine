#pragma once
#include "../ECS/World.h"
#include "ShaderData.h"
#include "TransformData.h"
#include "../Math/Math.h"
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
						glm::mat4 matrix(1.0f);
						matrix = matrix * glm::mat4_cast(transform.rotation);
						matrix = glm::scale(matrix, transform.scale);
						matrix = glm::translate(matrix, transform.position);
						shader.shader->Use();
						//TODO: USE CONST STRING
						shader.shader->SetMat4("model", matrix);
					}
				});
		}
	};
}