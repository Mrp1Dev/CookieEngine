#pragma once
#include <glm/glm.hpp>
#include <Usings.h>
#include <Math/Mathf.h>
#include <glm/gtc/quaternion.hpp>
#include <Math/Vector3.h>
namespace cookie
{
    namespace math
    {
        template<typename T>
        class QuaternionT
        {
            using quat = glm::tquat<T>;
        public:
            template<typename InputType>
            QuaternionT(const InputType x, const InputType y, const InputType z, const InputType w) noexcept :
                x { scast<T>(x) },
                y { scast<T>(y) },
                z { scast<T>(z) },
                w { scast<T>(w) }
            {
            };

            QuaternionT(const quat& q) noexcept :
                x { q.x },
                y { q.y },
                z { q.z },
                w { q.w }
            {
            };

            static QuaternionT<T> Euler(const T x, const T y, const T z) noexcept
            {
                return QuaternionT<T> { quat{glm::vec3(x, y, z)} };
            }

            static QuaternionT<T> Euler(const Vector3& v) noexcept
            {
                return QuaternionT<T> { quat{glm::vec3(v.x, v.y, v.z)} };
            }

            static QuaternionT<T> Identity() noexcept
            {
                return QuaternionT<T>(0, 0, 0, 1);
            }

            static T Dot(const QuaternionT<T>& lhs, const QuaternionT<T>& rhs)
            {
                return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
            }

            operator quat() const noexcept
            {
                return quat { w, x, y, z};
            }

            QuaternionT<T> operator*(const QuaternionT<T>& rhs) const noexcept
            {
                return scast<quat>(*this) * scast<quat>(rhs);
            }

            Vector3 operator*(const Vector3& rhs) const noexcept 
            {
                return scast<quat>(*this) * scast<glm::vec3>(rhs);
            }

            bool operator==(const QuaternionT<T>& rhs) const noexcept
            {
                return Mathf::Approximately(Dot(*this, rhs), 1.0f);
            }

            bool operator!=(const QuaternionT<T>& rhs) const noexcept
            {
                return !(*this == rhs);
            }

            Vector3 EulerAngles() const noexcept
            {
                return glm::eulerAngles(scast<quat>(*this));
            }

            Mat4 ToMatrix()
            {
                return glm::mat4_cast(scast<quat>(*this));
            }

            T x {};
            T y {};
            T z {};
            T w {};
        };

        using Quaternion = QuaternionT<f32>;
    }
}
