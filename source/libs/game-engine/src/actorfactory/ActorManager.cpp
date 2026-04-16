#include <vector>
#include <numeric>
#include <algorithm>

#include "ActorManager.hpp"

namespace ActorManager
{
	ActorManager::ActorManager()
	{
		mActorPool.reserve(mActorAmount);
		for (int i = 0; i < mActorAmount; i++)
		{
			// Because the Actor constructor is private, we can't use make_shared when creating the new Actor
			// we need to create the raw pointer and wrap it.
			mActorPool.push_back(std::shared_ptr<Actor::Actor>(new Actor::Actor(createdActors++)));
		}

		mFreeActors.reserve(mActorAmount);
		//std::iota(mFreeActors.begin(), mFreeActors.end(), 0); not working for some reason
		for (int i = 0; i < mActorAmount; i++)
			mFreeActors.push_back(i);

		mActiveActors.reserve(mActorAmount);
		mToAdd.reserve(mActorAmount);
		mToDestroy.reserve(mActorAmount);

	}

	ActorPtr ActorManager::createActor(Actor::ActorTypeEnum actorType)
	{ 
		if (!mFreeActors.empty())
		{
			size_t freeActorIndex = mFreeActors.back();
			mFreeActors.pop_back();

			std::shared_ptr<Actor::Actor> newActor = mActorPool[freeActorIndex];
			newActor->init(actorType);

			mToAdd.push_back(newActor->getId());

			return newActor;
		}

		std::cout << "ERROR: New actor could not be created. Vector full." << std::endl;
		return nullptr;	
	}

	void ActorManager::destroyActor(int actorId)
	{
		if (mActorPool[actorId]->isAlive())
		{
			mActorPool[actorId]->destroy();
			mToDestroy.push_back(actorId);
		}
	}

	ActorVector& ActorManager::getActorsOfType(Actor::ActorTypeEnum actorType)
	{
		if (mActorsPerType.find(actorType) == mActorsPerType.end())
		{
			mActorsPerType[actorType] = ActorVector{};
			mActorsPerType[actorType].reserve(100);
		}

		return mActorsPerType[actorType];
	}

	const std::vector<size_t>& ActorManager::getAllActors() const
	{
		return mActiveActors;
	}

	ActorPtr ActorManager::getActor(Actor::ActorTypeEnum actorType, int actorId)
	{
		ActorVector actorGroup = mActorsPerType[actorType];

		for (auto it = actorGroup.begin(); it != actorGroup.end(); ++it)
		{
			if ((*it)->getId() == actorId)
			{
				return (*it);
				break;
			}				
		}

		return nullptr;
	}

	ActorPtr ActorManager::getActor(int actorId)
	{ 
		return mActorPool[actorId];
	}

	void ActorManager::update()
	{		
		// Remove destroyed
		for (auto actor : mToDestroy)
		{
			// Remove from actives
			auto actorToDeleteIndex = std::find(mActiveActors.begin(), mActiveActors.end(), actor);
			if (actorToDeleteIndex != mActiveActors.end())
			{
				// Find the actor to delete in the pool
				auto actorToDelete = mActorPool[*actorToDeleteIndex];

				// Erase from Type dictionary
				ActorVector& actorGroup = mActorsPerType[actorToDelete->getTag()];
				for (auto it2 = actorGroup.begin(); it2 != actorGroup.end(); ++it2)
				{
					if ((*it2)->getId() == (*actorToDeleteIndex))
					{
						actorGroup.erase(it2);
						break;
					}
				}

				// Erase from list of active actors
				mActiveActors.erase(actorToDeleteIndex);
			}
			// Add to free
			mFreeActors.push_back(actor);
		}
		mToDestroy.clear();


		//Add all new actors
		for (auto actor : mToAdd)
		{
			mActiveActors.push_back(actor);
			mActorsPerType[mActorPool[actor]->getTag()].push_back(mActorPool[actor]);
		}
		mToAdd.clear();		
	}
}