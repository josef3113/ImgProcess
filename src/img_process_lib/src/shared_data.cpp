#include "shared_data.h"



namespace img_process {

    SharedMemory::SharedMemory(img_process::SharedMutexes* shared_mutexs,
                               img_process::SharedVector* shared_vec)
        : shared_mutexes_{ shared_mutexs }
        , shared_vec_{ shared_vec }
    {}



    int SharedMemory::GetNumProcesses()
    {
        int idx_of_num_processers = 1;

        return (*shared_vec_)[idx_of_num_processers];
    }



    int SharedMemory::GetNextImgId()
    {
        int idx_of_num_img = 0;

        int val = -1;

        {// lock the mutex of img id to process.
            bi::scoped_lock<bi::interprocess_mutex> lock(shared_mutexes_->img_id_process_mutex);

            val = (*shared_vec_)[idx_of_num_img];

            (*shared_vec_)[idx_of_num_img]--;
        }// unlock the mutex.

        return val;
    }



    int SharedMemory::GetImgIdToSave()
    {
        int idx_of_last_save_img_id = 2;

        int id_to_return = -1;

        {// lock the mutex of last save img id.
            bi::scoped_lock<bi::interprocess_mutex> lock(shared_mutexes_->last_save_img_id_mutex);

            id_to_return = ++(*shared_vec_)[idx_of_last_save_img_id];
        }// ulock the mutex.

        return id_to_return;
    }
}