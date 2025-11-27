#include "CTransform.hpp"

namespace Component
{
	CTransform::CTransform(const Tools::Vec2<float>& pPosition, const Tools::Vec2<float>& pSpeed, const Tools::Vec2<float>& pScale, float pAngle) : position(pPosition), speed(pSpeed), scale(pScale), angle(pAngle)
	{
		exists = true;
	}
}