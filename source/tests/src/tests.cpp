#include <gtest/gtest.h>

#include "engine/engine.hpp"


// Demonstrate some basic assertions.
TEST(EngineTest, BasicAssertions) {
	// Expect two strings not to be equal.
	EXPECT_STRNE("hello", "world");
	// Expect equality.
	EXPECT_EQ(7 * 6, 42);

	double expected = 4.0;
	double result = mysqrt(2.0);

	EXPECT_DOUBLE_EQ(expected, result);
}