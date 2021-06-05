#include "ModelRenderingSystem.h"
#include "../Constants/ShaderUniforms.h"
#include <usings.h>
#include <glm/gtc/matrix_transform.hpp>
namespace cookie
{
    using namespace math;
    void ModelRenderingSystem::Update(World* world)
    {
        auto query { world->QueryEntities<ModelRendererData, ShaderData, TransformData>() };
        query->EntityForeach([this, &world](Entity entity, auto& model, ShaderData& shader, TransformData& transform)
            {
                if (model.enabled)
                {
                    for (auto& mesh : model.model->meshes)
                    {
                        Mat4 matrix(1.0f);
                        matrix = matrix * transform.rotation.ToMatrix();
                        matrix = Matrixf::Scale(matrix, transform.scale);
                        matrix = Matrixf::Translate(matrix, transform.position);
                        shader.shader->Use();
                        shader.shader->SetMat4(ShaderUniforms::MODEL_MATRIX, matrix);
                        shader.shader->SetMat4(ShaderUniforms::INV_MODEL_MATRIX, Matrixf::Inverse(matrix));
                        auto baseColor = world->TryGetComponent<BaseColorData>(entity);
                        if (baseColor.has_value())
                        {
                            shader.shader->SetVec3(ShaderUniforms::BASE_COLOR, baseColor.value()->color);
                        }

                        DrawMesh(shader.shader, mesh);
                        shader.shader->SetVec3(ShaderUniforms::BASE_COLOR, 1, 1, 1);
                    }
                }
            });
    }
    void ModelRenderingSystem::DrawMesh(Shader* shader, Mesh& mesh)
    {
        i32 diffuseNumber { -1 };
        i32 specularNumber { -1 };
        for (u32 i = 0; i < mesh.textures.size(); i++)
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
        shader->SetInt(ShaderUniforms::DIFFUSE_TEXTURE_COUNT, diffuseNumber + 1);
        shader->SetInt(ShaderUniforms::SPECULAR_TEXTURE_COUNT, specularNumber + 1);
        glActiveTexture(GL_TEXTURE0);

        glBindVertexArray(mesh.VAO);
        glDrawElements(GL_TRIANGLES, scast<GLsizei>(mesh.indices.size()), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
}