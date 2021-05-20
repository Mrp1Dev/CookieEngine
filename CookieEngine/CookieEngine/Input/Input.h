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
		std::vector<Key> keys {};
		std::array<bool, KEYS> previousFramePressed {};
		bool lockCursor {};
		glm::vec2 mousePosition {};
		glm::vec2 mouseDelta {};
		glm::vec2 previousFramePos {};
	};
}