#include <vector>
#include <numeric>
#include <algorithm>

#include "ActorManager.hpp"

namespace ActorManager
{
	ActorManager::ActorManager()
	{
		mActorPool.reserve(mActorAmount);
		for (ActorVector::iterator it = mActorPool.begin(); it != mActorPool.end(); it++)
		{
			// Because the Actor constructor is private, we can't use make_shared when creating the new Actor
			// we need to create the raw pointer and wrap it.
			mActorPool.push_back(std::shared_ptr<Actor::Actor>(new Actor::Actor(createdActors++)));
		}

		mFreeActors.reserve(mActorAmount);
		std::iota(std::begin(mFreeActors), std::end(mFreeActors), 0);

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
			newActor->removeAll();

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
		return mActorsPerType[actorType];
	}

	ActorVector& ActorManager::getAllActors()
	{
		return mActorPool;
	}

	ActorPtr ActorManager::getActor(Actor::ActorTypeEnum actorType, int actorId)
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
		// Remove destroyed
		for (auto actor : mToDestroy)
		{
			// Remove from actives
			auto it = std::find(mActiveActors.begin(), mActiveActors.end(), actor);
			if (it != mActiveActors.end())
				mActiveActors.erase(it);

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