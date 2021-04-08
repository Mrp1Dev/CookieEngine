#pragma once
#include <unordered_map>
#include <memory>
#include "Ref.h"

namespace cookie
{
	class Entity
	{
	public:
		std::unordered_map<size_t, std::shared_ptr<BaseRef>> components;
		bool IsAlive { true };
	};

	
}