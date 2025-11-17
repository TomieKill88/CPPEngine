#include "Vec2.hpp"

namespace Linear
{	
	Vec2::Vec2(float xin, float yin) : x(xin), y(yin) {}

	void Vec2::add(const Vec2& other)
	{
		x += other.x;
		y += other.y;
	}
	void Vec2::sub(const Vec2& other)
	{ 
		x -= other.x;
		y -= other.y;
	}
	void Vec2::mult(float val)
	{ 
		x *= val;
		y *= val;
	}

	Vec2& Vec2::operator= (const Vec2& lhs)
	{
		this->x = lhs.x;
		this->y = lhs.y;

		return *this;
	}
	Vec2  Vec2::operator+ (const Vec2& lhs)
	{
		Vec2 result(0.0f, 0.0f);

		result.x = this->x + lhs.x;
		result.y = this->y + lhs.y;

		return result;
	}
	Vec2  Vec2::operator- (const Vec2& lhs)
	{
		Vec2 result(0.0f, 0.0f);

		result.x = this->x - lhs.x;
		result.y = this->y - lhs.y;

		return result;
	}
	float Vec2::operator* (const Vec2& lhs)
	{
		float result = (this->x * lhs.x) + (this->y * lhs.y);

		return result;
	}
	Vec2& Vec2::operator+=(const Vec2& lhs)
	{
		this->x += lhs.x;
		this->y += lhs.y;

		return *this;
	}
	Vec2& Vec2::operator-=(const Vec2& lhs)
	{
		this->x -= lhs.x;
		this->y -= lhs.y;

		return *this;
	}
	bool  Vec2::operator==(const Vec2& lhs)
	{
		return (this->x == lhs.x) && (this->y == lhs.y);
	}
}