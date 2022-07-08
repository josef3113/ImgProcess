#pragma once
#include "black_white_img.h"
#include <boost/filesystem.hpp>


namespace img_process {
    int BlackWhiteImg::last_save_img_ = 0;


    BlackWhiteImg::BlackWhiteImg(const std::string& input_folder_path,
                                 const std::string& output_folder_path,
                                 const std::string& img_name)
    {
        // read imag 
        ReadImg(input_folder_path, img_name);

        // converct img to black & white.
        img_ = ConvertImgBGRtoBW::Convert(img_, multipliers_);

        // save image
        SaveImg(output_folder_path);
    }



    void BlackWhiteImg::ReadImg(const std::string& folder_name, const std::string& img_name)
    {
        std::string img_path = folder_name + "/" + img_name;
        img_ = cv::imread(img_path, cv::IMREAD_COLOR);

        if (img_.empty()) {
            throw std::runtime_error("cannot read img " + img_path);
        }
    }


    bool BlackWhiteImg::SaveImg(const std::string& out_folder_name)
    {
        int save_id = -1;
        {// lock when take the id of img that save.
            std::lock_guard lg(increment_id_mtx_);
            save_id = last_save_img_++;
        }// unlock

        boost::filesystem::create_directory(out_folder_name);

        std::string save_path_name = out_folder_name +
                                     "/ image_" +
                                     std::to_string(save_id) + ".png";
         
        return cv::imwrite(save_path_name, img_);
    }
}