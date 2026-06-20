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
		removeAll();
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
		std::string tagid = tag.toString() + std::to_string(id);
		return tagid;
	}

	sf::Text Actor::renderTagString(sf::Font& font)
	{
		sf::Text label(font);
		label.setString(getTagString());
		label.setOrigin(label.getLocalBounds().getCenter());
		label.setPosition(get<Components::CShape>().shape.getPosition());

		return label;
	}

	void Actor::destroy()
	{
		mAlive = false;
	}

	void Actor::removeAll()
	{
		remove<Components::CTransform>();
		remove<Components::CCollision>();
		remove<Components::CInput>();
		remove<Components::CLifespan>();
		remove<Components::CScore>();
		remove<Components::CShape>();
	}
}
