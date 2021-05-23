#include "SetPerspectiveMatrixSystem.h"
#include "../Constants/ShaderUniforms.h"
namespace cookie
{
	void SetPerspectiveMatrixSystem::Update(World* world)
	{
		auto cameraQuery { world->QueryEntities<CameraData>() };
		bool doesCamExist { false };
		CameraData* cam { nullptr };
		auto* window { world->GetResource<Window>() };
		cameraQuery->Foreach([&doesCamExist, &window, &cam](CameraData& camera)
			{
				if (camera.isActive)
				{
					doesCamExist = true;
					cam = &camera;
				}
			});
		if (doesCamExist)
		{
			auto perspectiveMatrix =
				glm::perspective(
					glm::radians(cam->fov),
					(float)window->width / (float)window->height,
					cam->nearClippingPlane,
					cam->farClippingPlane
				);

			auto query { world->QueryEntities<ShaderData>() };
			query->Foreach([perspectiveMatrix](ShaderData& shader)
				{
					shader.shader->Use();
					shader.shader->SetMat4(ShaderUniforms::PROJECTION_MATRIX, perspectiveMatrix);
				});
		}
	}
}