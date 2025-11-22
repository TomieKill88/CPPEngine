#pragma once

#include <memory>

#include "Actor.hpp"
#include "ActorType.hpp"
#include "src/Component.hpp"

namespace Actor
{
	typedef std::shared_ptr<Actor> ActorPtr;
	typedef std::vector<ActorPtr> ActorVector;

	class ActorManager
	{
	private:

		ActorVector mActiveActors;
		ActorVector mToAdd;
		std::map<ActorTypeEnum, ActorVector> mActorsPerType;

		

	public:

		size_t createdActors = 0;

		ActorManager();

		~ActorManager() = default;

		ActorPtr createActor(ActorTypeEnum actorType);
		ActorVector& getActorsOfType(ActorTypeEnum actorType);
		ActorVector& getAllActors();
		ActorPtr getActor(ActorTypeEnum actorType, int actorId);
		void update();
		void destroy();
	};
}
