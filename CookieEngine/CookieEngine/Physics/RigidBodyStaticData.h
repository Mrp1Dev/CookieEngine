#pragma once
#include <PxRigidStatic.h>

namespace cookie::physics
{
	struct RigidBodyStaticData
	{
		physx::PxRigidStatic* pxRb { nullptr };
		bool initialized { false };
	};
}