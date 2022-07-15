#pragma once 
#include "black_white_img.h"
#include "shared_data.h"
#include <iostream>



namespace img_process {

    // multi process img processor.
    class MPBlackWhiteImg : public BlackWhiteImg {
    public:
        MPBlackWhiteImg(const std::string& input_folder_path,
                        const std::string& output_folder_path,
                        const std::string& img_name,
                        SharedMemory& shared_memory);

    protected:
        virtual int GetLastImgIdSaved() override;

    private:
        SharedMemory& shared_memory_;
    };
}