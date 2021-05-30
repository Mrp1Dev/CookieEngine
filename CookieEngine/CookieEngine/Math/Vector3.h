#pragma once
#include <glm/glm.hpp>
#include <Usings.h>
#include <Math/Mathf.h>

namespace cookie
{
    namespace math
    {
        template<typename T>
        class Vector3T
        {
            using vec3 = glm::tvec3<T>;
        public:
            template<typename InputType>
            Vector3T(const InputType x, const InputType y, const InputType z) noexcept :
                x { scast<T>(x) },
                y { scast<T>(y) },
                z { scast<T>(z) }
            {
            };

            Vector3T(const vec3& v) noexcept :
                x { v.x },
                y { v.y },
                z { v.z }
            {
            };

            static Vector3T<T> Splat(T f) noexcept
            {
                return Vector3T<T>(f, f, f);
            }

            static Vector3T<T> Forward() noexcept
            {
                return Vector3T<T>(0, 0, 1);
            }

            static Vector3T<T> Right() noexcept
            {
                return Vector3T<T>(1, 0, 0);
            }

            static Vector3T<T> Up() noexcept
            {
                return Vector3T<T>(0, 1, 0);
            }

            static Vector3T<T> Left()  noexcept
            {
                return Vector3T<T>(-1, 0, 0);
            }

            static Vector3T<T> Down() noexcept
            {
                return Vector3T<T>(0, -1, 0);
            }

            static Vector3T<T> Back() noexcept
            {
                return Vector3T<T>(0, 0, -1);
            }

            static Vector3T<T> One() noexcept
            {
                return Vector3T<T>::Splat(1);
            }

            static Vector3T<T> Zero() noexcept
            {
                return Vector3T<T>::Splat(0);
            }

            static T Dot(const Vector3T<T>& lhs, const Vector3T<T>& rhs)
            {
                return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
            }

            static T Angle(const Vector3T<T>& lhs, const Vector3T<T>& rhs) noexcept
            {
                T denominator = Mathf::Sqrt(lhs.SqrMagnitude() * rhs.SqrMagnitude());
                if (denominator < 0.001f) return 0.0f;

                T dot = Mathf::Clamp(Dot(lhs, rhs) / denominator, -1.0f, 1.0f);
                return Mathf::Acos(dot);
            }

            T Magnitude() const noexcept
            {
                return glm::length(scast<vec3>(*this));
            }

            T SqrMagnitude() const noexcept
            {
                return x * x + y * y + z * z;
            }

            Vector3T Normalized() const noexcept
            {
                return *this / Magnitude();
            }

            void Normalize() noexcept
            {
                *this = Normalized();
            }

            operator vec3() const noexcept
            {
                return vec3 { x, y, z };
            }

            Vector3T<T> operator+(const Vector3T<T>& rhs) const noexcept
            {
                return Vector3T<T>(x + rhs.x, y + rhs.y, z + rhs.z);
            }

            Vector3T<T> operator-(const Vector3T<T>& rhs) const noexcept
            {
                return Vector3T<T>(x - rhs.x, y - rhs.y, z - rhs.z);
            }

            Vector3T<T> operator-() const noexcept
            {
                return Vector3T<T>(-x, -y, -z);
            }

            Vector3T<T> operator*(const T scalar) const noexcept
            {
                return Vector3T<T>(x * scalar, y * scalar, z * scalar);
            }

            Vector3T<T> operator/(const T f) const noexcept
            {
                return Vector3T<T>(x / f, y / f, z / f);
            }

            bool operator==(const Vector3T<T>& rhs) const noexcept
            {
                return Mathf::Approximately(x, rhs.x)
                    && Mathf::Approximately(y, rhs.y)
                    && Mathf::Approximately(z, rhs.z);
            }

            Vector3T<T> operator+=(const Vector3T<T>& rhs) noexcept
            {
                return *this = *this + rhs;
            }

            T x {};
            T y {};
            T z {};

            const static Vector3T<T> forward;
        };

        using Vector3 = Vector3T<f32>;
        using Vector3Int = Vector3T<i32>;
    }
}