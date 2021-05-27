#pragma once
#include <glm/glm.hpp>
namespace cookie
{
    namespace math
    {
        class Vector3
        {
            Vector3(f32 x, f32 y, f32 z) : vec { x, y, z }
            {
            };
        private:
            glm::vec3 vec {};
        };
    }
}