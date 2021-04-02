#pragma once
#include <typeinfo>

namespace cookie
{
	class Component
	{
	public:
		virtual std::type_info Type() = 0;
	};
}