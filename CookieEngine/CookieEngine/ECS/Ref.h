#pragma once
#include <optional>
#include <vector>

namespace cookie
{
	template<class T>
	class Ref
	{
	public:
		std::vector<std::optional<T>>* vector;
		unsigned int index;
		Ref(std::vector<std::optional<T>>* vector, unsigned int index)
			: vector { vector }, index { index }
		{

		};

		T& operator*()
		{
			return vector->at(index).value();
		}

		T* operator->()
		{
			return &vector->at(index).value();
		}
	};
}
