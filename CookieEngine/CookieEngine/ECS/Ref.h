#pragma once

namespace cookie
{
	class BaseRef
	{
	};
	template<class T>
	class Ref : public BaseRef
	{
<<<<<<< HEAD
		std::vector<T>* vector;
		unsigned int index;
	public:
		Ref(std::vector<T>* vector, unsigned int index)
=======
		std::vector<std::optional<T>>* vector;
		unsigned int index;
	public:
		Ref(std::vector<std::optional<T>>* vector, unsigned int index)
>>>>>>> origin/PreRefactorizationBranch
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
