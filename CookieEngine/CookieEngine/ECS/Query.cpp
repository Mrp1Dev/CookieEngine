#include "Query.h"

namespace cookie
{
	template<class ...QueryTypes>
	template<class F>
	inline void Query<QueryTypes...>::Foreach(F&& function)
	{
		for (auto& tuple : query)
		{
			function(*std::get<cookie::Ref<QueryTypes>>(tuple)...);
		}
	}

	template<class ...QueryTypes>
	template<class F>
	inline void Query<QueryTypes...>::EntityForeach(F function)
	{
		for (unsigned int i = 0; i < query.size(); i++)
		{
			function(entities.at(i), *std::get<cookie::Ref<QueryTypes>>(query.at(i))...);
		}
	}
}