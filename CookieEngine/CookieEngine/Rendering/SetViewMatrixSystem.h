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
		virtual void Update(World* world) override
		{
			auto cameraQuery { world->QueryEntities<CameraData, TransformData>() };
			auto shaderQuery { world->QueryEntities<ShaderData>() };
			cameraQuery->Foreach([&shaderQuery](CameraData& camera, TransformData& transform)
				{
					if (camera.isActive)
					{
						shaderQuery->Foreach([&transform](ShaderData& shader)
							{
								//TODO: CONST STRINGS
								shader.shader->SetMat4(
									"view",
									glm::lookAt(
										transform.position,
										transform.rotation * glm::vec3(0, 0, 1),
										transform.rotation * glm::vec3(0, 1, 0)
									)
								);
							});
					}
				});
		}
	};
}