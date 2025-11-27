#pragma once

#include "Component.hpp"

namespace Component
{
	class CLifeSpawn : public Component
	{

	public:

		int life = 0;
		int remaining = 0;

		CLifeSpawn() = default;
		CLifeSpawn(int pLife);

		virtual ~CLifeSpawn() = default;
	};
}
