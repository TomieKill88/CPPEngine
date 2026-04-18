#include "Vec2.hpp"

namespace Tools
{	

	float Vec2::fastInvSqrt(float number)
	{
		// https://www.geeksforgeeks.org/dsa/fast-inverse-square-root/

		const float threehalfs = 1.5F;

		float x2 = number * 0.5F;
		float y = number;

		// evil floating point bit level hacking 
		long i = *(long*)&y;

		// value is pre-assumed 
		i = 0x5f3759df - (i >> 1);
		y = *(float*)&i;

		// 1st iteration 
		y = y * (threehalfs - (x2 * y * y));

		// 2nd iteration, this can be removed 
		// y = y * ( threehalfs - ( x2 * y * y ) ); 

		return y;
	}

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
	float Vec2::len()
	{
		float num = (x * x) + (y * y);
		float invLen = fastInvSqrt(num);
		if (invLen == 0.0)
			return 0.0;

		return 1 / invLen;
	}
	float Vec2::lenSquared()
	{
		return (x * x) + (y * y);
	}
	float Vec2::dist(const Vec2& other)
	{ 
		return 1 / fastInvSqrt(distSquared(other));
	}
	float Vec2::distSquared(const Vec2& other)
	{
		return (other.x - x) * (other.x - x) + (other.y - y) * (other.y - y);
	}
	void Vec2::normalize()
	{
		float num = (x * x) + (y * y);
		float invLen = fastInvSqrt(num);

		x = x * invLen;
		y = y * invLen;
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