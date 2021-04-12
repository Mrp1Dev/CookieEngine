#pragma once

namespace cookie
{
	template<class T>
	class Ref
	{
		std::vector<std::optional<T>>* vector;
		unsigned int index;
	public:
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
