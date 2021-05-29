#pragma once
#include <glm/glm.hpp>
#include <Usings.h>
#include <Math/Mathf.h>

namespace cookie
{
    namespace math
    {
        class Vector3 : public glm::vec3
        {
            template<typename T>
            Vector3(T x, T y, T z) noexcept : glm::vec3 { scast<f32>(x), scast<f32>(y), scast<f32>(z) }
            {
            };

            Vector3(const glm::vec3& v) noexcept : glm::vec3 {v}
            {
            }

            static Vector3 Splat(f32 f) noexcept
            {
                return Vector3(f, f, f);
            }

            static Vector3 Forward() noexcept
            {
                return Vector3(0, 0, 1);
            }

            static Vector3 Right() noexcept
            {
                return Vector3(1, 0, 0);
            }

            static Vector3 Up() noexcept
            {
                return Vector3(0, 1, 0);
            }

            static Vector3 Left()  noexcept
            {
                return Vector3(-1, 0, 0);
            }

            static Vector3 Down() noexcept
            {
                return Vector3(0, -1, 0);
            }

            static Vector3 Back() noexcept
            {
                return Vector3(0, 0, -1);
            }

            static Vector3 One() noexcept
            {
                return Vector3::Splat(1);
            }

            static Vector3 Zero() noexcept
            {
                return Vector3::Splat(0);
            }

            /*static f32 Dot(const Vector3& lhs, const Vector3& rhs)
            {
                return lhs.vec.x * rhs.x + 
            }*/

            static f32 Angle(const Vector3& lhs, const Vector3& rhs) noexcept
            {
                f32 denominator = Mathf::Sqrt(lhs.SqrMagnitude() * rhs.SqrMagnitude());
                if (denominator < 0.001f) return 0.0f;

                f32 dot = Mathf::Clamp(glm::dot(scast<glm::vec3>(lhs), scast<glm::vec3>(rhs)) / denominator, -1.0f, 1.0f);
            }

            Vector3 operator+(const Vector3& rhs) const noexcept
            {
                return Vector3(scast<glm::vec3>(*this) + rhs);
            }
            
            Vector3 operator-(const Vector3& rhs) const noexcept
            {
                return Vector3(scast<glm::vec3>(*this) - rhs);
            }
            
            Vector3 operator-() const noexcept
            {
                return Vector3(-scast<glm::vec3>(*this));
            }

            Vector3 operator*(f32 scalar) const noexcept
            {
                return Vector3(scast<glm::vec3>(*this) * scalar);
            }

            Vector3 operator/(f32 f) const noexcept
            {
                return Vector3(scast<glm::vec3>(*this) / f);
            }

            f32 Magnitude() const noexcept
            {
                return glm::length(*this);
            }
            
            f32 SqrMagnitude() const noexcept
            {
                return vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;
            }

            Vector3 Normalized() const noexcept
            {
                return *this / Magnitude();
            }

            void Normalize() noexcept
            {
                vec = Normalized();
            }

        };
    }
}