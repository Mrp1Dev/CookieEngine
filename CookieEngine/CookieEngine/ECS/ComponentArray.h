#pragma once
#include <vector>
#include <optional>
#include <Usings.h>
namespace cookie
{
	class BaseComponentArray
	{
	public:
		virtual void clear(u32 index) = 0;
	};

	template<class T>
	class ComponentArray : public BaseComponentArray
	{
	public:
		std::vector<std::optional<T>> Components;

		ComponentArray(std::vector<std::optional<T>> components) : Components { components }
		{
		}

		void clear(u32 index) override
		{
			Components.at(index).reset();
		}

		std::vector<std::optional<T>>& operator*()
		{
			return Components;
		}
	};
	
}