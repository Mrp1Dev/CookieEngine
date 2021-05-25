#include "SetViewMatrixSystem.h"
#include "../Constants/ShaderUniforms.h"
namespace cookie
{
	void SetViewMatrixSystem::Update(World* world)
	{
		auto cameraQuery { world->QueryEntities<CameraData, TransformData>() };
		auto shaderQuery { world->QueryEntities<ShaderData>() };
		cameraQuery->Foreach([&](CameraData& camera, TransformData& transform)
			{
				if (camera.isActive)
				{
					shaderQuery->Foreach([&](ShaderData& shader)
						{
							shader.shader->SetMat4(
								ShaderUniforms::VIEW_MATRIX,
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