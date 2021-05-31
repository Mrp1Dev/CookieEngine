#include "Matrix.h"
#include <glm/gtc/matrix_transform.hpp>
namespace cookie
{
    namespace math
    {
        namespace Matrixf
        {
            Mat4 LookAt(const Vector3& eye, const Vector3& center, const Vector3& up) noexcept
            {
                return glm::lookAt(scast<glm::vec3>(eye), scast<glm::vec3>(center), scast<glm::vec3>(up));
            }

            Mat4 Scale(const Mat4& mat, const Vector3& scalar) noexcept
            {
                return glm::scale(mat, scast<glm::vec3>(scalar));
            }

            Mat4 Translate(const Mat4& mat, const Vector3& translation) noexcept
            {
                return glm::translate(mat, scast<glm::vec3>(translation));
            }

            Mat4 Inverse(const Mat4& mat) noexcept
            {
                return glm::inverse(mat);
            }
        }
    }
}