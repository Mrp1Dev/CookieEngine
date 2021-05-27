#pragma once
#include <usings.h>
namespace cookie
{
	struct CameraData
	{
	public:
		f32 fov {};
		bool isActive {};
		f32 nearClippingPlane {};
		f32 farClippingPlane {};
	};
}