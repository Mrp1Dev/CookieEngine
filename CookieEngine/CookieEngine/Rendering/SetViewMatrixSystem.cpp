#include "SetViewMatrixSystem.h"
#include "../Constants/ShaderUniforms.h"
#include <glm/gtc/matrix_transform.hpp>
#include <ckMath.h>
namespace cookie
{
	using namespace math;
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
								Matrixf::LookAt(
									transform.position,
									transform.position + (transform.rotation * Vector3::Forward()),
									transform.rotation * Vector3::Up()
								)
							);
						});
				}
			});

	}
}