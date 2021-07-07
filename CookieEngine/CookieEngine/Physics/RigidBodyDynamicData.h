#pragma once
#include <PxRigidDynamic.h>

namespace cookie::physics
{
	struct RigidBodyDynamicData
	{
		physx::PxRigidDynamic* pxRb { nullptr };
		bool initialized { false };
	};
}