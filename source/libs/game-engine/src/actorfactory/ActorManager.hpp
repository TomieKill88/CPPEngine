#pragma once

#include <memory>

#include "Actor.hpp"
#include "ActorType.hpp"
#include "Components.hpp"

namespace ActorManager
{
	typedef std::shared_ptr<Actor::Actor> ActorPtr;
	typedef std::vector<ActorPtr> ActorVector;

	class ActorManager
	{
	private:

		size_t mActorAmount = 10000;
		ActorVector mActorPool;
		std::vector<size_t> mToAdd;
		std::vector<size_t> mToDestroy;
		std::vector<size_t> mActiveActors;
		std::vector<size_t> mFreeActors;
		std::map<Actor::ActorTypeEnum, ActorVector> mActorsPerType;

	public:

		size_t createdActors = 0;

		ActorManager();

		~ActorManager() = default;

		ActorPtr createActor(Actor::ActorTypeEnum actorType);
		void destroyActor(int actorId);
		ActorVector& getActorsOfType(Actor::ActorTypeEnum actorType);
		const std::vector<size_t>& getAllActors() const;
		ActorPtr getActor(Actor::ActorTypeEnum actorType, int actorId);
		ActorPtr getActor(int actorId);
		void update();
	};
}
