#pragma once
#include "../ECS/World.h"
#include "ShaderData.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "TransformData.h"
#include "CameraData.h"
#include "../ResourceTypes/Window.h"

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
			auto* window { world->GetResource<Window>() };
			cameraQuery->Foreach([&doesCamExist, &FOV, &window](CameraData& camera)
				{
					if (camera.isActive)
					{
						doesCamExist = true;
						FOV = camera.FOV;
					}
				});
			if (doesCamExist)
			{
				auto perspectiveMatrix =
					glm::perspective(glm::radians(FOV), (float)window->width / (float)window->height, 0.1f, 10000.0f);
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