#pragma once
#include "../ECS/World.h"
#include "ModelRendererData.h"
#include "ShaderData.h"
#include "TransformData.h"
#include "BaseColorData.h"

namespace cookie
{
	class ModelRenderingSystem : public System
	{
	public:
		virtual void Update(World* world) override
		{
			auto query { world->QueryEntities<ModelRendererData, ShaderData, TransformData>() };
			query->EntityForeach([this, &world](Entity entity, auto& model, ShaderData& shader, auto& transform)
				{
					if (model.enabled)
					{
						for (auto& mesh : model.model->meshes)
						{
							glm::mat4 matrix(1.0f);
							matrix = matrix * glm::mat4_cast(transform.rotation);
							matrix = glm::scale(matrix, transform.scale);
							matrix = glm::translate(matrix, transform.position);
							shader.shader->Use();
							//TODO: USE CONST STRINGS
							shader.shader->SetMat4("model", matrix);
							auto baseColor = world->TryGetComponent<BaseColorData>(entity);
							if (baseColor.has_value())
							{
								shader.shader->SetVec4("material.baseColor", baseColor.value()->color);
							}

							DrawMesh(shader.shader, mesh);
							shader.shader->SetVec4("material.baseColor", glm::vec4(1, 1, 1, 1));
						}
					}
				});
			
		}
		void DrawMesh(Shader* shader, Mesh& mesh)
		{
			int diffuseNumber { -1 };
			int specularNumber { -1 };
			shader->SetBool("material.hasTexture", mesh.Textures.size() != 0);
			for (unsigned int i = 0; i < mesh.Textures.size(); i++)
			{
				glActiveTexture(GL_TEXTURE0 + i);

				std::string number;
				std::string name = mesh.Textures[i].Type;
				//TODO: CONST HERE
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
