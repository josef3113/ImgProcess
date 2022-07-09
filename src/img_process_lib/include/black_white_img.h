#pragma once
#include <mutex>
#include "convert_img.h"



namespace img_process {

    // class the get path and name of image,load the img ,convert to black/white and save the result.
    class BlackWhiteImg {
    public:
        BlackWhiteImg(std::string input_folder_path,
            std::string output_folder_path,
            std::string img_name);

        void Do();

    protected:
        virtual int GetLastImgIdSaved();

    private:

        void ReadImg(const std::string& folder_name, const std::string& img_name);

        bool SaveImg(const std::string& folder_name);

        std::mutex increment_id_mtx_;

        static int last_save_img_;

        cv::Mat img_;

        ConvertImgBGRtoBW::BGRMultipliers multipliers_{ 0.299,0.587,0.114 };

        std::string input_folder_path_;
        std::string output_folder_path_; 
        std::string img_name_;

    };
}
