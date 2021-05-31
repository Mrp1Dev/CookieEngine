#pragma once
#include <Usings.h>
namespace cookie
{
	class Time
	{
	public:
		f32 deltaTime { 0.0f };
		f32 time { 0.0f };
		f32 fixedDeltaTime { 0.0f };
	};
}