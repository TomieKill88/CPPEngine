#pragma once

namespace Linear
{
	class Vec2
	{
	public:

		float x = 0.0f;
		float y = 0.0f;

		Vec2() = default;
		Vec2(float xin, float yin);
		~Vec2() = default;

		void add(const Vec2& other);
		void sub(const Vec2& other);
		void mult(float val);

		Vec2& operator= (const Vec2& lhs);
		Vec2  operator+ (const Vec2& lhs);
		Vec2  operator- (const Vec2& lhs);
		float operator* (const Vec2& lhs);
		Vec2&  operator+=(const Vec2& lhs);
		Vec2&  operator-=(const Vec2& lhs);
		bool  operator==(const Vec2& lhs);

	};
}