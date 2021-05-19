#pragma once
#include <unordered_map>
#include <array>
#include "Key.h"
#include "KeyCode.h"

namespace cookie
{
	
	class Input
	{
	public:
		std::array<Key, KEYS> keys {Key(0)};
		std::array<bool, KEYS> previousFramePressed {};
	};
}