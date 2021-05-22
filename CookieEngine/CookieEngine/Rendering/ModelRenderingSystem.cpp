#include "ModelRenderingSystem.h"

namespace cookie
{
	const std::string MODEL_UNIFORM = "model";
	const std::string BASE_COLOR_UNIFORM = "material.baseColor";
	const std::string HAS_TEXTURE_UNIFORM = "material.hasTexture";
	void ModelRenderingSystem::Update(World* world)
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
						shader.shader->SetMat4(MODEL_UNIFORM, matrix);
						auto baseColor = world->TryGetComponent<BaseColorData>(entity);
						if (baseColor.has_value())
						{
							shader.shader->SetVec4(BASE_COLOR_UNIFORM, baseColor.value()->color);
						}

						DrawMesh(shader.shader, mesh);
						shader.shader->SetVec4(BASE_COLOR_UNIFORM, glm::vec4(1, 1, 1, 1));
					}
				}
			});

	}
	void ModelRenderingSystem::DrawMesh(Shader* shader, Mesh& mesh)
	{
		int diffuseNumber { -1 };
		int specularNumber { -1 };
		shader->SetBool(HAS_TEXTURE_UNIFORM, mesh.Textures.size() != 0);
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
}