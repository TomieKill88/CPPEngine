#include "CTransform.hpp"

namespace Component
{
	CTransform::CTransform(const Tools::Vec2& pPosition, const Tools::Vec2& pSpeed) : position(pPosition), speed(pSpeed)
	{
		exists = true;
	}
}