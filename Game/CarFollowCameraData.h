#pragma once
#include <ECS/Entity.h>
#include <ckMath.h>
struct CarFollowCameraData
{
	cookie::Entity car;
	cookie::math::Vector3 baseOffset {};
	cookie::math::Quaternion baseRotation { cookie::math::Quaternion::Identity() };
};