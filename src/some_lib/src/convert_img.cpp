#include "convert_img.h"


namespace some_lib {

    cv::Mat ConvertImgBGRtoBW::Convert(const cv::Mat& origin_img,
                                       ConvertImgBGRtoBW::BGRMultipliers multipliers)
    {
        cv::Mat img_res(origin_img.rows, origin_img.cols, 1);

        for (int i = 0; i < origin_img.rows; i++) {
            for (int j = 0; j < origin_img.cols; j++) {

                int sum = origin_img.at<cv::Vec3b>(i, j)[0] * multipliers.b_multipler_;
                sum += origin_img.at<cv::Vec3b>(i, j)[1] * multipliers.g_multipler_;
                sum += origin_img.at<cv::Vec3b>(i, j)[2] * multipliers.r_multipler_;

                img_res.at<uchar>(i, j) = sum;
            }
        }

        return img_res;
    }
}
