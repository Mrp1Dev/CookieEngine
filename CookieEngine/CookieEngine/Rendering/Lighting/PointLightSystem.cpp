#include "PointLightSystem.h"
#include "RenderingComponents.h"
#include "Constants.h"
#include <Rendering/Lighting/PointLightData.h>
#include <array>
namespace cookie
{
    void PointLightSystem::Update(World* world)
    {
        auto lights { world->QueryEntities<TransformData, PointLightData>() };
        auto objects { world->QueryEntities<TransformData, ShaderData>() };
        i32 lightCount {};

        objects->Foreach([&](TransformData& transform, ShaderData& shader)
            {
                lights->Foreach([&](TransformData& lightTransform, PointLightData& light)
                    {
                        if (lightCount + 1 > ShaderUniforms::PointLight::MAX_COUNT)
                        {
                            std::cout << "ERROR: MORE LIGHTS THAN THE LIMIT" << '\n';
                            return;
                        }

                        shader.shader->SetVec3(ShaderUniforms::PointLight::POSITIONS[lightCount], lightTransform.position);
                        shader.shader->SetVec3(ShaderUniforms::PointLight::DIFFUSE_COLORS[lightCount], light.color);
                        shader.shader->SetVec3(ShaderUniforms::PointLight::SPECULAR_COLORS[lightCount], light.specularColor);
                        shader.shader->SetFloat(ShaderUniforms::PointLight::RANGES[lightCount], light.range);
                        shader.shader->SetFloat(ShaderUniforms::PointLight::DIFFUSE_STRENGTHS[lightCount], light.diffuseStrength);
                        shader.shader->SetFloat(ShaderUniforms::PointLight::SPECULAR_STRENGTHS[lightCount], light.specularStrength);
                        shader.shader->SetInt(ShaderUniforms::PointLight::LIGHT_COUNT, ++lightCount);

                    });
            });
    }
}