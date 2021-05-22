#include "SetViewMatrixSystem.h"

namespace cookie
{
	void SetViewMatrixSystem::Update(World* world)
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
									transform.position + transform.rotation * glm::vec3(0, 0, 1),
									transform.rotation * glm::vec3(0, 1, 0)
								)
							);
						});
				}
			});
	}
}