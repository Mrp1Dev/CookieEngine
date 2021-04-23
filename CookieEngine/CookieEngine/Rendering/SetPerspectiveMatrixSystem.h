#pragma once
#include "../ECS/World.h"
#include "ShaderData.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "TransformData.h"
#include "CameraData.h"

namespace cookie
{
	class SetPerspectiveMatrixSystem : public System
	{
	public:
		virtual void Start(World* world) override
		{
			std::cout << "Start called on setperspectivemtrix\n";
		}

		virtual void Update(World* world) override
		{
			auto cameraQuery { world->QueryEntities<CameraData>() };
			bool doesCamExist { false };
			float FOV { 60.0f };
			cameraQuery->Foreach([&doesCamExist, &FOV](CameraData& camera)
				{
					if (camera.isActive)
					{
						doesCamExist = true;
						FOV = camera.FOV;
					}
				});
			if (doesCamExist)
			{
				//TODO: USE ACTUAL SCREEN SIZE
				auto perspectiveMatrix =
					glm::perspective(glm::radians(FOV), (float)1280 / (float)720, 0.1f, 100.0f);
				auto query { world->QueryEntities<ShaderData>() };
				query->Foreach([perspectiveMatrix](ShaderData& shader)
					{
						shader.shader->Use();
						//TODO: USE A CONST STRING FOR SHADER UNIFORM
						shader.shader->SetMat4("projection", perspectiveMatrix);
					});
			}
		}
	};
}