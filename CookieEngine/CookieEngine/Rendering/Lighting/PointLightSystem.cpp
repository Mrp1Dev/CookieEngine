#include "PointLightSystem.h"
#include "RenderingComponents.h"
#include "Constants.h"
#include <Rendering/Lighting/PointLightData.h>
namespace cookie
{
    void PointLightSystem::Update(World* world)
    {
        auto lights { world->QueryEntities<TransformData, PointLightData>() };
        auto objects { world->QueryEntities<TransformData, ShaderData>() };
        int lightCount {};

        objects->Foreach([&](TransformData& transform, ShaderData& shader)
            {
                lights->Foreach([&](TransformData& lightTransform , PointLightData& light)
                    {
                        lightCount++;
                        shader.shader->SetInt(ShaderUniforms::PointLight::LIGHT_COUNT, lightCount);
                        shader.shader->SetVec3(ShaderUniforms::PointLight::Position(lightCount - 1), lightTransform.position);
                        shader.shader->SetVec3(ShaderUniforms::PointLight::DiffuseColor(lightCount - 1), light.color);
                        shader.shader->SetVec3(ShaderUniforms::PointLight::SpecularColor(lightCount - 1), light.specularColor);
                    });
            });
    }
}