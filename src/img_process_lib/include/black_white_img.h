#pragma once
#include <mutex>
#include "convert_img.h"



namespace img_process {

    // class that gets path and name of image, load the img ,convert to black/white and saves the result.
    class BlackWhiteImg {
    public:
        BlackWhiteImg(const std::string& input_folder_path,
                      const std::string& output_folder_path,
                      const std::string& img_name);

    private:

        void ReadImg(const std::string& folder_name, const std::string& img_name);

        bool SaveImg(const std::string& folder_name);

        std::mutex increment_id_mtx_;

        static int last_save_img_;

        cv::Mat img_;

        ConvertImgBGRtoBW::BGRMultipliers multipliers_{ 0.299,0.587,0.114 };
    };
}
