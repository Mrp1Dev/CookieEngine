#pragma once
#include "Ref.h"
#include "Entity.h"
#include <vector>
#include <functional>

namespace cookie
{
	class QueryBase
	{

	};
	template<class... QueryTypes>
	class Query : public QueryBase
	{
	public:
		std::vector<Entity> entities;
		std::vector<std::tuple<cookie::Ref<QueryTypes>...>> query;
		Query(std::vector<std::tuple<cookie::Ref<QueryTypes>...>>& query, std::vector<Entity>& entities)
			: query { std::move(query) }, entities { std::move(entities) }
		{
		};

		template<class F>
		void Foreach(F&& function);

		template<class F>
		void EntityForeach(F function);
	};
	
	
}