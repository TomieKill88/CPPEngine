#pragma once

#include <iostream>
#include <string>
#include <memory>

#include <SFML/Graphics.hpp>

#include "ActorType.hpp"
#include "src/CTransform.hpp"
#include "src/CInput.hpp"
#include "src/CLifeSpawn.hpp"
#include "src/CScore.hpp"
#include "src/CCollision.hpp"
#include "src/CColor.hpp"
#include "src/CShape.hpp"

namespace Actor
{	
	class ActorManager;

	typedef std::tuple<Component::CShape, 
						Component::CTransform, 
						Component::CColor, 
						Component::CInput, 
						Component::CCollision, 
						Component::CLifeSpawn, 
						Component::CScore> 
		ComponentTuple;

	class Actor
	{
		friend class ActorManager;
	private:

		ActorType tag;

		size_t id = 0;

		ComponentTuple mComponents;

		bool mAlive = false;

		Actor() = default;
		Actor(ActorTypeEnum actorType, size_t id);	public:

	public:

		virtual ~Actor() = default;

		bool isAlive() const;
		size_t getId() const;
		ActorTypeEnum getTag();
		std::string getTagString();

		void destroy();

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
