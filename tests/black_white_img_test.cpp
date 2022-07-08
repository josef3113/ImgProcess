#include <gtest/gtest.h>
#include "black_white_img.h"
#include <boost/filesystem.hpp>



TEST(ConvertBGRtoBWImageTest, basic_test)
{
    std::string image_path = cv::samples::findFile("starry_night.jpg");
    cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);

    float b_multiple = 0.299;
    float g_multiple = 0.587;
    float r_multiple = 0.114;

    img_process::ConvertImgBGRtoBW::BGRMultipliers multipliers{ b_multiple,
                                                                g_multiple,
                                                                r_multiple };

    auto res_img = img_process::ConvertImgBGRtoBW::Convert(img, multipliers);

    boost::filesystem::create_directory("output test");

    cv::imwrite("output test/origin.png", img);
    cv::imwrite("output test/result.png", res_img);

    std::cout << "# check output test folder" << std::endl;
}




TEST(BwImageTest, basic_test)
{
    int img_id = 1;

    EXPECT_NO_THROW(img_process::BlackWhiteImg("data",
                                                "output test",
                                                std::to_string(img_id) + ".JPG"));

}