#include <stdlib.h>
#include <ctime>

#include "BasicTools.hpp"

namespace Tools
{
	void seed()
	{
		srand(std::time(0));
	}
	float getRandomFloat(float min, float max)
	{
		float num = (float)(rand() % (int)(max - min + 1));
		return num + min;
	}

	int getRandomInt(int min, int max)
	{
		int num = rand() % (max - min + 1);
		return num + min;
	}
}