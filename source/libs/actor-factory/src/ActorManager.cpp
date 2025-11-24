#include "ActorManager.hpp"

namespace Actor
{
	ActorManager::ActorManager()
	{
		mActiveActors.reserve(1000);
		mToAdd.reserve(50);
	}

	ActorPtr ActorManager::createActor(ActorTypeEnum actorType)
	{ 
		// Because the Ator onstructor is private, we can't use make_shared when creating the new Actor
		// we need to create the raw pointer and wrap it.
		std::shared_ptr<Actor> newActor = std::shared_ptr<Actor>(new Actor(actorType, createdActors++));
		mToAdd.push_back(newActor);
		return newActor;
	}

	ActorVector& ActorManager::getActorsOfType(ActorTypeEnum actorType)
	{
		return mActorsPerType[actorType];
	}

	ActorVector& ActorManager::getAllActors()
	{
		return mActiveActors;
	}

	ActorPtr ActorManager::getActor(ActorTypeEnum actorType, int actorId)
	{
		ActorVector actorGroup = mActorsPerType[actorType];

		for (auto it = actorGroup.begin(); it != actorGroup.end(); ++it)
		{
			if (!(*it)->getId() == actorId)
			{
				return (*it);
				break;
			}				
		}

		return nullptr;
	}

	void ActorManager::update()
	{		
		// Destroy all marked Actors
		for (auto it = mActiveActors.begin(); it != mActiveActors.end(); ++it)
		{
			if (!(*it)->isAlive())
				it = mActiveActors.erase(it);

			// Needed because if erase returns end, the for check fails.
			if (it == mActiveActors.end())
				break;
		}
		for (auto& mapEntry : mActorsPerType)
		{
			ActorVector& actorGroup = mapEntry.second;

			for (auto it = actorGroup.begin(); it != actorGroup.end(); ++it)
			{
				if (!(*it)->isAlive())
					it = actorGroup.erase(it);

				// Needed because if erase returns end, the for check fails.
				if (it == actorGroup.end())
					break;
			}
		}

		//Add all new actors
		for (auto actor : mToAdd)
		{
			mActiveActors.push_back(actor);
			mActorsPerType[actor->getTag()].push_back(actor);
		}

		mToAdd.clear();
	}
}