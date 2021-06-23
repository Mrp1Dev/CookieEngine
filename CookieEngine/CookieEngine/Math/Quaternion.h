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
                auto result { QuaternionT<T>::Identity() };
                const T s = Mathf::Sin(angle * scast<T>(0.5));

                result.w = Mathf::Cos(angle * scast<T>(0.5));
                result.x = axis.x * s;
                result.y = axis.y * s;
                result.z = axis.z * s;
                return result;
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

                f32 cosTheta = Vector3T<T>::Dot(start, dest);
                Vector3T<T> rotationAxis;

                if (cosTheta < -1 + 0.001f)
                {
                    // special case when vectors in opposite directions :
                    // there is no "ideal" rotation axis
                    // So guess one; any will do as long as it's perpendicular to start
                    // This implementation favors a rotation around the Up axis,
                    // since it's often what you want to do.
                    rotationAxis = Vector3T<T>::Cross(Vector3T<T>::Forward(), start);
                    if (rotationAxis.SqrMagnitude() < 0.01) // bad luck, they were parallel, try again!
                        rotationAxis = Vector3T<T>::Cross(Vector3T<T>::Right(), start);

                    rotationAxis.Normalize();
                    return AngleAxis(Mathf::Deg2Rad * 180.0f, rotationAxis);
                }

                // Implementation from Stan Melax's Game Programming Gems 1 article
                rotationAxis = Vector3T<T>::Cross(start, dest);

                f32 s = Mathf::Sqrt((1 + cosTheta) * 2);
                f32 invs = 1 / s;

                return QuaternionT<T>(
                    rotationAxis.x * invs,
                    rotationAxis.y * invs,
                    rotationAxis.z * invs,
                    s * 0.5f
                );
            }

            static QuaternionT<T> LookRotation(Vector3T<T> direction, Vector3T<T> desiredUp = Vector3T<T>::Up())
            {

                if (direction.SqrMagnitude() < 0.0001f)
                    return QuaternionT<T>::Identity();

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

            T x {};
            T y {};
            T z {};
            T w {};
        };

        using Quaternion = QuaternionT<f32>;
    }
}
