#pragma once

namespace Tools
{
	namespace General
	{
		template<typename T>
		T random(T min, T max)
		{
			static bool first = true;
			if (first)
			{
				srand(time(NULL)); //seeding for the first time only!
				first = false;
			}
			return min + rand() % (int)((max + 1) - min);
		}
	}
}