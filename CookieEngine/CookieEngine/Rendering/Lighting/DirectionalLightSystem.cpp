#include "DirectionalLightSystem.h"
#include "RenderingComponents.h"
#include "DirectionalLightData.h"
#include <Constants.h>
#include <ckMath.h>
namespace cookie
{
    using namespace cookie::math;
    void DirectionalLightSystem::Start(World* world)
    {
        world->EnqueueEntitySpawn(DirectionalLightData {
            math::Vector3(-1, -1, -1),
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