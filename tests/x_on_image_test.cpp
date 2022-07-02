#include <gtest/gtest.h>
#include "x_on_image.h"


TEST(XOnImageTest, basic_test)
{
	int img_id = 1;
	
	some_lib::XOnImage{ "empty_path ", img_id };
}