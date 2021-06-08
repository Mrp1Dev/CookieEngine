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
            Quaternion::Euler(Mathf::PI/4.0f, 0.0f, 0.0f) * math::Vector3::Down(),
            math::Vector3::Splat(0.8f),
            math::Vector3::Splat(0.15f)
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