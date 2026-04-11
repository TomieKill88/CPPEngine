#include "Actor.hpp"

namespace Actor
{
	Actor::Actor(size_t id) : id(id)
	{
		tag.setEnum(ActorTypeEnum::NONE);
	}

	Actor::Actor(ActorTypeEnum actorType, size_t id) : id(id)
	{
		init(actorType);
	}

	void Actor::init(ActorTypeEnum actorType)
	{
		tag.setEnum(actorType);
		mAlive = true;
	}

	bool Actor::isAlive() const
	{
		return mAlive;
	}

	size_t Actor::getId() const
	{
		return id;
	}

	ActorTypeEnum Actor::getTag()
	{
		return tag.getEnum();
	}	

	std::string Actor::getTagString()
	{
		return tag.toString();
	}

	void Actor::destroy()
	{
		mAlive = false;
	}	
}
