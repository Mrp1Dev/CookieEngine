#pragma once
#include <optional>
#include <vector>
#include <Usings.h>
namespace cookie
{
	template<class T>
	class Ref
	{
	public:
		std::vector<std::optional<T>>* vector;
		u32 index;
		Ref(std::vector<std::optional<T>>* vector, u32 index)
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
