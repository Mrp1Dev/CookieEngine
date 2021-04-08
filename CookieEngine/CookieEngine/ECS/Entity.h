#pragma once
#include <map>
#include <memory>
#include "Ref.h"

namespace cookie
{
	class Entity
	{
	public:
		std::map<size_t, std::shared_ptr<BaseRef>> components;
		bool IsAlive { true };
	};

	
}