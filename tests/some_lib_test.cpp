#include <gtest/gtest.h>



TEST(BasicTest, basic_test)
{
	auto expected = 1;

	auto actual = 1;

	EXPECT_EQ(actual, expected);
}