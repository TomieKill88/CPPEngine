#include "Components.hpp"

namespace Components
{
	CTransform::CTransform(const Tools::Science::Vec2& pPosition, const Tools::Science::Vec2& pSpeed) : position(pPosition), speed(pSpeed)
	{
		exists = true;
	}

	CCollision::CCollision(float radius) : mRadius(radius)
	{
		exists = true;
		mShape.setRadius(radius);
		mShape.setPointCount(20);
		mShape.setFillColor(sf::Color(0,0,0,0));
		mShape.setOutlineColor(sf::Color::Red);
		mShape.setOutlineThickness(1.0);
		mShape.setOrigin(mShape.getLocalBounds().getCenter());
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
		mShape.setOrigin(mShape.getLocalBounds().getCenter());
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