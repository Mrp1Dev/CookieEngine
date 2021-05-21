#include "ComponentArray.h"

namespace cookie
{
	template<class T>
	void ComponentArray<T>::clear(unsigned int index)
	{
		Components.at(index).reset();
	}

	template<class T>
	std::vector<std::optional<T>>& ComponentArray<T>::operator*()
	{
		return Components;
	}
}