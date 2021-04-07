#pragma once

namespace cookie
{
	class BaseRef
	{
	};
	template<class T>
	class Ref : public BaseRef
	{
		std::vector<T>* vector;
		unsigned int index;
	public:
		Ref(std::vector<T>* vector, unsigned int index)
			: vector { vector }, index { index }{};
		T& operator*()
		{
			return vector->at(index);
		}

		T* operator->()
		{
			return &vector->at(index);
		}
	};
}
