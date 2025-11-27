#pragma once

#include <cmath>
#include <sstream>

#include <SFML/Graphics.hpp>

namespace Tools
{
	template<typename T>
	class Vec2
	{
	public:

		T x = 0.0f;
		T y = 0.0f;

		Vec2() = default;
		Vec2(T xin, T yin) : x(xin), y(yin) {};
		Vec2(const sf::Vector2<T>& lhs) : x(lhs.x), y(lhs.y) {};
		~Vec2() = default;

		void add(const Vec2& other)
		{
			x += other.x;
			y += other.y;
		}
		void sub(const Vec2& other)
		{
			x -= other.x;
			y -= other.y;
		}
		void mult(float val)
		{
			x *= val;
			y *= val;
		}
		T dist(const Vec2& other)
		{
			sf::Vector2f
			return std::sqrtf((other.x - this->x) * (other.x - this->x) + (other.y - this->y) * (other.y - this->y));
		}
		T len()
		{
			return std::sqrtf((this->x * this->x) + (this->y * this->y));
		}
		T lenSqr()
		{
			return ((this->x * this->x) + (this->y * this->y));
		}
		Vec2 normalized()
		{
			Vec2 tmp;
			float d = len();
			tmp.x = this->x / d;
			tmp.y = this->y / d;

			return tmp;
		}

		std::string toString()
		{
			std::stringstream ss;

			ss << "{ " << this->x << ", " << this->y << " }";
			return ss.str();
		}

		Vec2& operator= (const Vec2& lhs)
		{
			this->x = lhs.x;
			this->y = lhs.y;

			return *this;
		}
		Vec2& operator= (const sf::Vector2<T>& lhs)
		{
			this->x = lhs.x;
			this->y = lhs.y;

			return *this;
		}
		operator sf::Vector2<T>()
		{
			return sf::Vector2<T>(this->x, this->y);
		}
		Vec2 operator+ (const Vec2& lhs)
		{
			Vec2 result(0.0f, 0.0f);

			result.x = this->x + lhs.x;
			result.y = this->y + lhs.y;

			return result;
		}
		Vec2 operator- (const Vec2& lhs)
		{
			Vec2 result(0.0f, 0.0f);

			result.x = this->x - lhs.x;
			result.y = this->y - lhs.y;

			return result;
		}
		float operator* (const Vec2& lhs)
		{
			float result = (this->x * lhs.x) + (this->y * lhs.y);

			return result;
		}
		Vec2& operator+=(const Vec2& lhs)
		{
			this->x += lhs.x;
			this->y += lhs.y;

			return *this;
		}
		Vec2& operator-=(const Vec2& lhs)
		{
			this->x -= lhs.x;
			this->y -= lhs.y;

			return *this;
		}
		bool operator==(const Vec2& lhs)
		{
			return (this->x == lhs.x) && (this->y == lhs.y);
		}

	};

	// Define the most common types
	using Vec2i = Vec2<int>;
	using Vec2u = Vec2<unsigned int>;
	using Vec2f = Vec2<float>;
}