#pragma once
#include <ckMath.h>
namespace cookie::physics
{
	/// THE ENTITY MUST HAVE A ModelRendererDara and a TransformData Component if you use this.
	struct MeshColliderData
	{
		math::Vector3  offset {};
		bool convex { false };
	};
}