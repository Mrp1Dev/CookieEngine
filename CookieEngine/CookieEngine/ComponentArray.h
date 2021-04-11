#pragma once
#include <vector>
#include <optional>

namespace cookie
{
	class BaseComponentArray
	{
	public:
		virtual void clear(unsigned int index) = 0;
	};
	template<class T>
	class ComponentArray : public BaseComponentArray
	{
	public:
		std::vector<std::optional<T>> Components;

		ComponentArray(std::vector<std::optional<T>> components) : Components { components }
		{
		}

		void clear(unsigned int index) override
		{
			Components.at(index).reset();
		}

		std::vector<std::optional<T>>& operator*()
		{
			return Components;
		}
	};
}