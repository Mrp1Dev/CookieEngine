#pragma once
#include <Usings.h>
#include <ECS/Entity.h>
#include <optional>
namespace cookie
{
	struct CameraData
	{
	public:
		f32 fov {};
		bool isActive {};
		f32 nearClippingPlane {};
		f32 farClippingPlane {};
		std::optional<Entity> parent;
	};
}