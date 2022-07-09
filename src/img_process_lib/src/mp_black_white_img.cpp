#include "mp_black_white_img.h"



namespace img_process {

    MPBlackWhiteImg::MPBlackWhiteImg(const std::string& input_folder_path,
                                     const std::string& output_folder_path,
                                     const std::string& img_name,
                                     img_process::SharedMutexes* shared_mutexs,
                                     img_process::SharedVector* shared_vec)
        :BlackWhiteImg{ input_folder_path, output_folder_path, img_name }
        , shared_mutexs_{ shared_mutexs }
        , shared_vec_{ shared_vec }{}



    int MPBlackWhiteImg::GetLastImgIdSaved()
    {
        int idx_of_last_save_img_id = 2;

        int id_to_return = -1;

        {// lock the mutex of last save img id.
            bi::scoped_lock<bi::interprocess_mutex> lock(shared_mutexs_->last_save_img_id_mutex);

            id_to_return = ++(*shared_vec_)[idx_of_last_save_img_id];
        }// ulock the mutex

        return id_to_return;
    }
}