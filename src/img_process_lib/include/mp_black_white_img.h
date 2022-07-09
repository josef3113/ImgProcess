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
                        img_process::SharedMutexes* shared_mutexs,
                        img_process::SharedVector* shared_vec);

    protected:
        virtual int GetLastImgIdSaved() override;

    private:
        img_process::SharedMutexes* shared_mutexs_;
        
        img_process::SharedVector* shared_vec_;
    };
}