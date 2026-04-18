#include "Components.hpp"

namespace Components
{
	CTransform::CTransform(const Tools::Vec2& pPosition, const Tools::Vec2& pSpeed) : position(pPosition), speed(pSpeed)
	{
		exists = true;
	}

	CCollision::CCollision(float radius) : mRadius(radius)
	{
		exists = true;
	}

	CScore::CScore(int score) : mScore(score)
	{
		exists = true;
	}

	CShape::CShape() : mLabel(mFont)
	{
	}

	CShape::CShape(float radius, sf::Font& font, int pointCount) : mFont(font), mLabel(font)
	{
		exists = true;
		mShape.setRadius(radius);
		mShape.setPointCount(pointCount);
	}

	CLifespan::CLifespan(int lifeFrames) : mLifeFrames(lifeFrames), mRemainingFrames(lifeFrames)
	{
		exists = true;
	}

	// bool is place holder so Input can be created as nonexistent
	CInput::CInput(int left, int right,
					int up, int down,
					int shoot) : mLeft(left), mRight(right), mUp(up), mDown(down), mShoot(shoot)
	{
		exists = true;
	}
}