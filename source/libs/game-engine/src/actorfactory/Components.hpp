#pragma once

#include <SFML/Graphics.hpp>

#include "src/science/Vec2.hpp"


namespace Components
{
	class Component
	{
	public:
		bool exists = false;
	};


	class CTransform : public Component
	{

	public:

		Tools::Science::Vec2 position = { 0.0f, 0.0f };
		Tools::Science::Vec2 speed = { 0.0f, 0.0f };

		CTransform() = default;
		CTransform(const Tools::Science::Vec2& pPosition, const Tools::Science::Vec2& pSpeed);

		virtual ~CTransform() = default;
	};

	class CCollision : public Component
	{

	public:

		bool mDraw = false;
		float mRadius = 0.0f;
		sf::CircleShape mShape;

		CCollision() = default;
		CCollision(float radius);

		virtual ~CCollision() = default;
	};

	class CScore : public Component
	{
	public:

		int mScore = 0;

		CScore() = default;
		CScore(int score);

		virtual ~CScore() = default;
	};

	class CShape : public Component
	{
	public:
		sf::CircleShape mShape;
		sf::Font mFont;
		sf::Text mLabel;

		CShape();
		CShape(float radius, sf::Font& font, int pointCount = 20);

		virtual ~CShape() = default;
	};

	// In frames
	class CLifespan : public Component
	{
	public:

		int mLifeFrames = 0;
		int mRemainingFrames = 0;

		CLifespan() = default;
		CLifespan(int lifeFrames);

		virtual ~CLifespan() = default;
	};

	class CInput : public Component
	{
	public:

		int mLeft = 0, mRight = 0;
		int mUp = 0, mDown = 0;
		int mShoot = 0;

		CInput() = default;
		CInput(int left, int right,
				int up, int down,
				int shoot);

		virtual ~CInput() = default;
	};
}
