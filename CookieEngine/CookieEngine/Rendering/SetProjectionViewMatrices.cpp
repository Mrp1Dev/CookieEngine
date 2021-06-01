#include "SetProjectionViewMatrices.h"
#include <RenderingComponents.h>
#include <Resources.h>
#include <Constants.h>
#include <glm/gtc/matrix_transform.hpp>
#include <ckMath.h>
namespace cookie
{
	using namespace math;
    void SetProjectionViewMatrices::Update(World* world)
    {
		auto cameraQuery { world->QueryEntities<CameraData, TransformData>() };
		bool doesCamExist { false };
		CameraData* cam { nullptr };
		TransformData* transform { nullptr };
		auto* window { world->GetResource<Window>() };
		cameraQuery->Foreach([&](CameraData& camera, TransformData& transformData)
			{
				if (camera.isActive)
				{
					doesCamExist = true;
					cam = &camera;
					transform = &transformData;
				}
			});
		if (doesCamExist)
		{
			auto perspectiveMatrix =
				glm::perspective(
					glm::radians(cam->fov),
					(f32)window->width / (f32)window->height,
					cam->nearClippingPlane,
					cam->farClippingPlane
				);

			auto query { world->QueryEntities<ShaderData>() };
			query->Foreach([&](ShaderData& shader)
				{
					shader.shader->Use();
					shader.shader->SetMat4(ShaderUniforms::PROJECTION_MATRIX, perspectiveMatrix);
					shader.shader->SetMat4(
						ShaderUniforms::VIEW_MATRIX,
						Matrixf::LookAt(
							transform->position,
							transform->position + (transform->rotation * Vector3::Forward()),
							transform->rotation * Vector3::Up()
						)
					);
				});
		}

    }
}