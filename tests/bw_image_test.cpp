#include <gtest/gtest.h>
#include "bw_image.h"
#include <boost/filesystem.hpp>



TEST(ConvertBGRtoBWImageTest, basic_test)
{
	std::string image_path = cv::samples::findFile("starry_night.jpg");
	cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);

	float b_multiple = 0.299;
	float g_multiple = 0.587;
	float r_multiple = 0.114;

	some_lib::ConvertBGRtoBW::BGRMultipliers multipliers{
		b_multiple,
		g_multiple,
		r_multiple };

	auto res_img = some_lib::ConvertBGRtoBW::Convert(img, multipliers);

	boost::filesystem::path dstFolder = "output test";
	boost::filesystem::create_directory(dstFolder);

	cv::imwrite("output test/origin.png", img);
	cv::imwrite("output test/result.png", res_img);
}




TEST(BwImageTest, basic_test)
{
	int img_id = 1;
	
	try {
		some_lib::BwImage{ "data", "empty_path", std::to_string(img_id) };
	}
	catch (std::exception ex) {
		std::cout << ex.what() << std::endl;

		EXPECT_EQ(1, 0);
	}
}