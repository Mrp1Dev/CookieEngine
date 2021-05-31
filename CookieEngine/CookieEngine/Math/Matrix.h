#pragma once
#include <glm/glm.hpp>
#include "Vector3.h"
namespace cookie
{
    namespace math
    {
        using Matrix4x4 = glm::mat4;
        using Mat4 = glm::mat4;

        namespace Matrixf
        {
            Mat4 LookAt(const Vector3& eye, const Vector3& center, const Vector3& up) noexcept;
            Mat4 Scale(const Mat4& mat, const Vector3& scalar) noexcept;
            Mat4 Translate(const Mat4& mat, const Vector3& translation) noexcept;
            Mat4 Inverse(const Mat4& mat) noexcept;
        }
    }
}