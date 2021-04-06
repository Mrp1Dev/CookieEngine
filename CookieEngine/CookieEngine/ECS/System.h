#pragma once

namespace cookie
{
	class World;
	class System
	{
	public:
		virtual void Start(World* world)
		{
		};

		virtual void Update(World* world)
		{
		};

		virtual void Destroy(World* world)
		{
		};
	};
}