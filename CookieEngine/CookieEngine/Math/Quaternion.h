#pragma once
#include <glm/glm.hpp>
#include <Usings.h>
#include <Math/Mathf.h>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Math/Vector3.h>
#include <PxPhysicsAPI.h>
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

            QuaternionT(const physx::PxQuat& q) noexcept :
                x { q.x },
                y { q.y },
                z { q.z },
                w { q.w }
            {
            };


            static QuaternionT<T> Euler(const T x, const T y, const T z) noexcept
            {
                return QuaternionT<T> { quat { glm::vec3(x, y, z) } };
            }

            static QuaternionT<T> Euler(const Vector3& v) noexcept
            {
                return QuaternionT<T> { quat { glm::vec3(v.x, v.y, v.z) } };
            }

            static QuaternionT<T> AngleAxis(f32 angle, const Vector3T<T>& axis)
            {
                return glm::angleAxis(angle, scast<glm::tvec3<T>>(axis));
            }

            static QuaternionT<T> Identity() noexcept
            {
                return QuaternionT<T>(0, 0, 0, 1);
            }

            static QuaternionT<T> FromMatrix(Mat4 mat)
            {
                return QuaternionT<T>(glm::quat_cast(mat));
            }

            static T Dot(const QuaternionT<T>& lhs, const QuaternionT<T>& rhs)
            {
                return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
            }
            
            static QuaternionT<T> RotationBetweenVectors(Vector3T<T> start, Vector3T<T> dest)
            {
                start.Normalize();
                dest.Normalize();

                f32 dot = Vector3::Dot(start, dest);
                if (dot > 0.999f) return Identity();
                if (dot < -0.999f)
                {
                    f32 x = abs(dest.x);
                    f32 y = abs(dest.y);
                    f32 z = abs(dest.z);

                    Vector3 other = x < y ? (x < z ? Vector3::Right() : Vector3::Forward()) : (y < z ? Vector3::Up() : Vector3::Forward());
                    auto cross = Vector3::Cross(dest, other);
                    cross.Normalize();
                    return QuaternionT<T>(cross.x, cross.y, cross.z, 0.0f);
                }

                QuaternionT<T> res { Identity() };
                Vector3 a = Vector3::Cross(start, dest);
                res.x = a.x;
                res.y = a.y;
                res.z = a.z;
                res.w = Mathf::Sqrt((start.SqrMagnitude()) * (dest.SqrMagnitude())) + Vector3::Dot(start, dest);
                res.Normalize();
                return res;
            }

            static QuaternionT<T> LookRotation(Vector3T<T> direction, Vector3T<T> desiredUp = Vector3T<T>::Up())
            {

                if (direction.SqrMagnitude() < 0.0001f)
                    return QuaternionT<T>::Identity();
                direction.Normalize();
                desiredUp.Normalize();
                // Recompute desiredUp so that it's perpendicular to the direction
                // You can skip that part if you really want to force desiredUp
                Vector3T<T> right = Vector3T<T>::Cross(direction, desiredUp);
                desiredUp = Vector3T<T>::Cross(right, direction);

                // Find the rotation between the front of the object (that we assume towards +Z,
                // but this depends on your model) and the desired direction
                QuaternionT<T> rot1 = RotationBetweenVectors(Vector3T<T>::Forward(), direction);
                // Because of the 1rst rotation, the up is probably completely screwed up. 
                // Find the rotation between the "up" of the rotated object, and the desired up
                Vector3T<T> newUp = rot1 * Vector3T<T>::Up();
                QuaternionT<T> rot2 = RotationBetweenVectors(newUp, desiredUp);

                // Apply them
                return rot2 * rot1; // remember, in reverse order.
            }


            operator quat() const noexcept
            {
                return quat { w, x, y, z };
            }

            operator physx::PxQuat() const noexcept
            {
                return physx::PxQuat(x, y, z, w);
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

            void Normalize()
            {
                *this = glm::normalize(scast<quat>(*this));
            }

            T x {};
            T y {};
            T z {};
            T w {};
        };

        using Quaternion = QuaternionT<f32>;
    }
}
