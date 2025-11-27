#pragma once

#include "Component.hpp"

namespace Component
{
	class CScore : public Component
	{

	public:

		int score = 0;

		CScore() = default;
		CScore(int pScore);

		virtual ~CScore() = default;
	};
}
