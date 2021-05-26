#include "ModelRenderingSystem.h"
#include "../Constants/ShaderUniforms.h"
namespace cookie
{
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
                        shader.shader->SetMat4(ShaderUniforms::MODEL_MATRIX, matrix);
                        shader.shader->SetMat4(ShaderUniforms::INV_MODEL_MATRIX, glm::inverse(matrix));
                        auto baseColor = world->TryGetComponent<BaseColorData>(entity);
                        if (baseColor.has_value())
                        {
                            shader.shader->SetVec4(ShaderUniforms::BASE_COLOR, baseColor.value()->color);
                        }

                        DrawMesh(shader.shader, mesh);
                        shader.shader->SetVec4(ShaderUniforms::BASE_COLOR, glm::vec4(1, 1, 1, 1));
                    }
                }
            });


    }
    void ModelRenderingSystem::DrawMesh(Shader* shader, Mesh& mesh)
    {
        int diffuseNumber { -1 };
        int specularNumber { -1 };
        for (unsigned int i = 0; i < mesh.textures.size(); i++)
        {
            glActiveTexture(GL_TEXTURE0 + i);

            std::string number;
            TextureType name = mesh.textures[i].type;
            if (name == TextureType::Diffuse)
            {
                shader->SetInt(
                    std::string { ShaderUniforms::DIFFUSE_TEXTURE_ARRAY } + "[" + std::to_string(diffuseNumber++) + "]",
                    i
                );
            }
            else if (name == TextureType::Specular)
            {
                shader->SetInt(
                    std::string { ShaderUniforms::SPECULAR_TEXTURE_ARRAY } + "[" + std::to_string(specularNumber++) + "]",
                    i
                );
            }

            glBindTexture(GL_TEXTURE_2D, mesh.textures[i].id);
        }
        shader->SetBool(ShaderUniforms::DIFFUSE_TEXTURE_COUNT, diffuseNumber);
        shader->SetBool(ShaderUniforms::SPECULAR_TEXTURE_COUNT, specularNumber);
        glActiveTexture(GL_TEXTURE0);

        glBindVertexArray(mesh.VAO);
        glDrawElements(GL_TRIANGLES, mesh.indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
}