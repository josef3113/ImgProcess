#include <gtest/gtest.h>
#include "image_math.h"



TEST(ImageMathTest, basic_test)
{
	some_lib::ImageMath calc;

	some_lib::Image img{ {1,2,3,4},{3,4,6,7} };

	std::vector<int> multiply{ 1, 2, 3,4 };

	auto result = calc.Dot(img, 4, multiply);

	EXPECT_EQ(result.at(0), 30);
	EXPECT_EQ(result.at(1), 57);
}



TEST(ImageMathTest, throw_exeption_test)
{
	some_lib::ImageMath calc;

	some_lib::Image img{ {1,2,3,4,5,6},{3,4,6,7,8,9} };

	some_lib::Image err_img{ {1,2,3,4,5},{3,4,6,7,8,9} };

	std::vector<int> multiply{ 1, 2, 3,4 };

	// size of multiply & num not equal.
	EXPECT_ANY_THROW(calc.Dot(img, 2, multiply));

	// image size not valid - diff size between rows.
	EXPECT_ANY_THROW(calc.Dot(err_img, 4, multiply));

	// img smaller than multiply that request.
	EXPECT_ANY_THROW(calc.Dot(img, 7, { 1,2,3,4,5,6,7 }));
}