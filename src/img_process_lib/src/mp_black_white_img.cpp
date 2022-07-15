#include "mp_black_white_img.h"



namespace img_process {

    MPBlackWhiteImg::MPBlackWhiteImg(const std::string& input_folder_path,
                                     const std::string& output_folder_path,
                                     const std::string& img_name,
                                     SharedMemory& shared_memory)
        : BlackWhiteImg{ input_folder_path, output_folder_path, img_name }
        , shared_memory_{shared_memory}
    {}



    int MPBlackWhiteImg::GetLastImgIdSaved()
    {
        return shared_memory_.GetImgIdToSave();
    }
}