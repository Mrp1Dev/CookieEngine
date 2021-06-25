#pragma once
#include <glm/glm.hpp>
#include <Usings.h>
#include <Math/Mathf.h>
#include <PxPhysicsAPI.h>

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

            Vector3T(const physx::PxVec3& v) noexcept :
                x { v.x },
                y { v.y },
                z { v.z }
            {
            };

            Vector3T() noexcept : x { scast<T>(0.0) }, y { scast<T>(0.0) }, z { scast<T>(0.0) }{};

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

            static T Dot(const Vector3T<T>& lhs, const Vector3T<T>& rhs) noexcept
            {
                return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
            }

            static Vector3T<T> Cross(const Vector3T<T>& lhs, const Vector3T<T>& rhs) noexcept
            {
                return glm::cross(scast<vec3>(lhs), scast<vec3>(rhs));
            }

            static T Angle(const Vector3T<T>& lhs, const Vector3T<T>& rhs) noexcept
            {
                T denominator = Mathf::Sqrt(lhs.SqrMagnitude() * rhs.SqrMagnitude());
                if (denominator < 0.001f) return 0.0f;

                T dot = Mathf::Clamp(Dot(lhs, rhs) / denominator, -1.0f, 1.0f);
                return Mathf::Acos(dot);
            }
            
            static Vector3T<T> ProjectOnPlane(const Vector3T<T>& vec, const Vector3T<T>& normal) noexcept
            {
                f32 sqrMag = normal.SqrMagnitude();
                if (sqrMag < Mathf::Epsilonf) return vec;
                auto dot = Dot(vec, normal);
                return vec - normal * dot / sqrMag;
            }

            static Vector3T<T> Project(const Vector3T<T> vector, const Vector3T<T> onto)
            {
                if(Mathf::Approximately(vector.SqrMagnitude(), 0.0f)) return Zero();
                f32 dot = Dot(vector.Normalized(), onto.Normalized());
                return vector * dot;
            }

            static Vector3T<T> ClampMagnitude(const Vector3T<T>& vec, const T& mag)
            {
                return vec.Normalized() * Mathf::Min(vec.Magnitude(), mag);
            }

            static Vector3T<T> MoveTowards(const Vector3T<T>& current, const Vector3T<T>& target, const T& maxDelta) noexcept
            {
                auto dir = target - current;
                if (dir.SqrMagnitude() <= maxDelta * maxDelta)
                {
                    return target;
                }
                return current + ClampMagnitude(dir, maxDelta);
            }

            static Vector3T<T> Lerp(const Vector3T<T>& start, const Vector3T<T>& end, T t) noexcept
            {
                return Vector3T<T>(
                    Mathf::Lerp(start.x, end.x, t),
                    Mathf::Lerp(start.y, end.y, t),
                    Mathf::Lerp(start.z, end.z, t)
                    );
            }

            static T SignedAngle(const Vector3T<T>& from, const Vector3T<T>& to, const Vector3T<T> axis) noexcept
            {
                f32 unsignedAngle = Angle(from, to);
                auto cross = Cross(from, to);
                f32 sign = Mathf::Sign(Dot(axis, cross));
                return unsignedAngle * sign;
            }

            f32 Magnitude() const noexcept
            {
                return glm::length(scast<glm::vec3>(*this));
            }

            f32 SqrMagnitude() const noexcept
            {
                return scast<f32>(x) * scast<f32>(x) + scast<f32>(y) * scast<f32>(y) + scast<f32>(z) * scast<f32>(z);
            }

            Vector3T Normalized() const noexcept
            {
                auto mag = Magnitude();
                if (mag < Mathf::Epsilon<T>) return Vector3T::Zero();
                return *this / Magnitude();
            }

            void Normalize() noexcept
            {
                *this = Normalized();
            }

            Vector3T ScaledBy(const Vector3T& rhs) const noexcept
            {
                return Vector3T<T>(x * rhs.x, y * rhs.y, z * rhs.z);
            }

            Vector3T X0Y() const noexcept
            {
                return Vector3T<T>(x, scast<T>(0.0), y);
            }

            Vector3T WithY(T newY) const noexcept
            {
                return Vector3T<T>(x, newY, z);
            }

            Vector3T WithZ(T newZ) const noexcept
            {
                return Vector3T<T>(x, newZ, z);
            }

            Vector3T WithX(T newX) const noexcept
            {
                return Vector3T<T>(x, newX, z);
            }

            Vector3T WithXY(T newX, T newY) const noexcept
            {
                return Vector3T<T>(newX, newX, z);
            }

            Vector3T WithXZ(T newX, T newZ) const noexcept
            {
                return Vector3T<T>(newX, y, newZ);
            }

            Vector3T WithYZ(T newY, T newZ) const noexcept
            {
                return Vector3T<T>(x, newY, newZ);
            }

            operator vec3() const noexcept
            {
                return vec3 { x, y, z };
            }

            operator physx::PxVec3() const noexcept
            {
                return physx::PxVec3{x, y, z};
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

            Vector3T<T> operator-=(const Vector3T<T>& rhs) noexcept
            {
                return *this = *this - rhs;
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