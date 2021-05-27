#pragma once
#include <glm/glm.hpp>
namespace cookie
{
    namespace math
    {
        class Vector3
        {
            Vector3(float x, float y, float z) : vec { x, y, z }
            {
            };
        private:
            glm::vec3 vec {};
        };
    }
}