#include "World.h"
#include <usings.h>
namespace cookie
{
	void World::StartSystems()
	{
		for (auto& system : this->systems)
		{
			system->Start(this);
		}
		auto commandsLength = scast<u32>(commands.size());
		for (u32 i = 0; i < commandsLength; i++)
		{
			commands.front()();
			commands.pop_front();
		}
	}

	void World::UpdateSystems()
	{
		auto commandsLength = scast<u32>(commands.size());
		for (u32 i = 0; i < commandsLength; i++)
		{
			commands.front()();
			commands.pop_front();
		}
		for (auto& system : this->systems)
		{
			system->Update(this);
		}
		queriesDirty = false;
	}

	void World::DestroySystems()
	{
		for (auto& system : this->systems)
		{
			system->Destroy(this);
		}
	}

	World* World::EnqueueEntityDespawn(Entity entity)
	{
		if (entity.gen == currentEntities.at(entity.index).gen)
		{
			auto f = std::bind(&World::despawnEntity, this, entity.index);
			commands.push_back(f);
		}
		return this;
	}

	void World::despawnEntity(u32 index)
	{
		despawnedEntities.push_back(index);
		currentEntities.at(index).gen++;
		for (auto& pair : ComponentsMap)
		{
			pair.second->clear(index);
		}
		queriesDirty = true;
	}

}