#pragma once
#include "Component.h"
#include <map>
#include <tuple>

namespace cookie
{
	
	class IncompleteEntity
	{
	public:

		template<class... Query>
		virtual std::tuple<Query*...> QueryEntity() = 0;
	};

	template<class... Archetype>
	class Entity: public IncompleteEntity
	{
		std::tuple<Archetype...> components;

	public:
		explicit Entity(Archetype... components) : components { components... }
		{
		};

		template<class... Query>
		virtual std::tuple<Query*...> QueryEntity() override
		{
			return std::tuple<Query*...>(&std::get<Query>(components)...);
		}
	};

	
}