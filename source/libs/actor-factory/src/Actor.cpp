#include "Actor.hpp"

namespace Actor
{
	Actor::Actor(ActorTypeEnum actorType, size_t id)
	{
		tag.setEnum(actorType);
		this->id = id;
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
