#include "DirectionalLightSystem.h"
#include "RenderingComponents.h"
#include "DirectionalLightData.h"
#include <Constants.h>
namespace cookie
{
    void DirectionalLightSystem::Start(World* world)
    {
        world->EnqueueEntitySpawn(DirectionalLightData {
            glm::fquat(glm::vec3(45, 0, 0)) * glm::vec3(0, -1, 0),
            glm::vec3(0.8f),
            glm::vec3(0.15f)
            });
    }

    void DirectionalLightSystem::Update(World* world)
    {
        auto shaderQuery { world->QueryEntities<ShaderData>() };
        auto lightQuery { world->QueryEntities<DirectionalLightData>() };
        lightQuery->Foreach([&shaderQuery](DirectionalLightData& light)
            {
                shaderQuery->Foreach([&light](ShaderData& shader)
                    {
                        shader.shader->SetVec3(ShaderUniforms::DirectionalLight::DIRECTION, light.direction);
                        shader.shader->SetVec3(ShaderUniforms::DirectionalLight::AMBIENT_COLOR, light.ambientColor);
                        shader.shader->SetVec3(ShaderUniforms::DirectionalLight::DIFFUSE_COLOR, light.color);
                        shader.shader->SetVec3(ShaderUniforms::DirectionalLight::SPECULAR_COLOR, light.color);
                    });
            });
    }
}