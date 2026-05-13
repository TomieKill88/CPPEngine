#include <math.h>
#include "Vec2.hpp"
#include "Math.hpp"

namespace Tools
{	
	namespace Science
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
		void Vec2::polar(float degree, float len)
		{
			float rad = degree * PI / 180;
			y = len * sinf(rad);
			x = len * cosf(rad);
		}
		float Vec2::len()
		{
			float num = (x * x) + (y * y);
			float invLen = fastInverseSqrt(num);
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
			return 1 / fastInverseSqrt(distSquared(other));
		}
		float Vec2::distSquared(const Vec2& other)
		{
			return (other.x - x) * (other.x - x) + (other.y - y) * (other.y - y);
		}
		void Vec2::normalize()
		{
			float num = (x * x) + (y * y);
			float invLen = fastInverseSqrt(num);

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
}