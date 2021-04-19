#pragma once
#include "../ECS/World.h"
#include "ModelRendererData.h"
#include "ShaderData.h"

namespace cookie
{
	class ModelRenderingSystem : public System
	{
	public:
		virtual void Update(World* world) override
		{
			auto query { world->QueryEntities<ModelRendererData, ShaderData>() };
			query->Foreach([this](auto& model, auto& shader)
				{
					if (model.enabled)
					{
						for (auto& mesh : model.model->meshes)
						{
							DrawMesh(shader.shader, mesh);
						}
					}
				});
		}
		void DrawMesh(Shader* shader, Mesh& mesh)
		{
			int diffuseNumber { -1 };
			int specularNumber { -1 };
			for (unsigned int i = 0; i < mesh.Textures.size(); i++)
			{
				glActiveTexture(GL_TEXTURE0 + i);

				std::string number;
				std::string name = mesh.Textures[i].Type;
				if (name == "texture_diffuse")
					number = std::to_string(diffuseNumber++);
				else if (name == "texture_specular")
					number = std::to_string(specularNumber++);

				shader->SetInt("material." + name + number, i);
				glBindTexture(GL_TEXTURE_2D, mesh.Textures[i].Id);
			}
			glActiveTexture(GL_TEXTURE0);

			glBindVertexArray(mesh.VAO);
			glDrawElements(GL_TRIANGLES, mesh.Indices.size(), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}
	};
}
