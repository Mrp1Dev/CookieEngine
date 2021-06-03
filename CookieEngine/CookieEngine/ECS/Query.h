#pragma once
#include "Ref.h"
#include "Entity.h"
#include <vector>
#include <functional>
#include <Usings.h>
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
		void Foreach(F&& function)
		{
			for (auto& tuple : query)
			{
				function(*std::get<cookie::Ref<QueryTypes>>(tuple)...);
			}
		}

		template<class F>
		void EntityForeach(F function)
		{
			for (u32 i = 0; i < query.size(); i++)
			{
				function(entities.at(i), *std::get<cookie::Ref<QueryTypes>>(query.at(i))...);
			}
		}

		u32 Length()
		{
			return query.size();
		}
	};
	
	
}