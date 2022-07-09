#pragma once 
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>



namespace img_process {

    class ConvertImgBGRtoBW {
    public:
        struct BGRMultipliers {

            BGRMultipliers(float b_multipler,
                           float g_multipler,
                           float r_multipler)
            :b_multipler_{ b_multipler }
            ,g_multipler_{ g_multipler }
            ,r_multipler_{ r_multipler }{}

            float b_multipler_;

            float g_multipler_;

            float r_multipler_;
        };

        static cv::Mat Convert(const cv::Mat& origin_img,
                               const ConvertImgBGRtoBW::BGRMultipliers& multipliers);
    };
}