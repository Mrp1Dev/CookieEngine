#pragma once

namespace cookie
{
	struct CameraData
	{
	public:
		float fov {};
		bool isActive {};
		float nearClippingPlane {};
		float farClippingPlane {};
	};
}