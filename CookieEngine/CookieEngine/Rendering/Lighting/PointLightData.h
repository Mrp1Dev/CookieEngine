#pragma once
#include <glm/glm.hpp>
namespace cookie
{
    struct PointLightData
    {
        glm::vec3 color {};
        glm::vec3 specularColor {};
        float range {};
    };
}