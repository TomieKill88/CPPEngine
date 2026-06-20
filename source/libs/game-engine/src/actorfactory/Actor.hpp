#pragma once

#include <iostream>
#include <string>
#include <memory>

#include <SFML/Graphics.hpp>

#include "ActorType.hpp"
#include "Components.hpp"


namespace ActorManager
{
	class ActorManager;
}

namespace Actor
{	
	// remember to update removeAll!!
	typedef std::tuple<Components::CTransform,
						Components::CCollision,
						Components::CInput,
						Components::CLifespan,
						Components::CScore,
						Components::CShape> ComponentTuple;

	class Actor
	{
		friend class ActorManager::ActorManager;
	private:

		ActorType tag;

		size_t id = 0;

		ComponentTuple mComponents;

		bool mAlive = false;

		// later private
		Actor() = default;
		Actor(size_t id);
		Actor(ActorTypeEnum actorType, size_t id);

		void init(ActorTypeEnum actorType);
		void removeAll();
		void destroy();

	public:


		virtual ~Actor() = default;

		bool isAlive() const;
		size_t getId() const;
		ActorTypeEnum getTag();
		std::string getTagString();

		sf::Text renderTagString(sf::Font& font);

		// COMPONENTS
		template<typename T>
		T& get()
		{
			return std::get<T>(mComponents);
		}
		template<typename T>
		const T& get() const
		{
			return std::get<T>(mComponents);
		}
		template<typename T>
		bool has()
		{
			return get<T>().exists;
		}
		template<typename T, typename... TArgs>
		T& add(TArgs&&... compArgs)
		{
			auto &component = get<T>();
			
			component = T(std::forward<TArgs>(compArgs)...);
			component.exists = true;

			return component;
		}
		template<typename T>
		void remove()
		{
			get<T>() = T();
		}
	};
}
