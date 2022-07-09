#include "shared_data.h"



namespace img_process {

    SharedMemory::SharedMemory()
    {
        //Open already created shared memory object.
        bi::shared_memory_object shm(bi::open_only, "MutexMemory", bi::read_write);

        //Map the whole shared memory in this process
        bi::mapped_region region(shm, bi::read_write);
        shared_mutexes_ = (img_process::SharedMutexes*)region.get_address();


        bi::managed_shared_memory segment(bi::open_only,
            "VectorMemory");  //segment name

        shared_vec_ = segment.find<img_process::SharedVector>("SharedVector").first;
    }



    int SharedMemory::GetNumProcesses() {
        int inx_of_num_processers = 1;

        return (*shared_vec_)[inx_of_num_processers];
    }



    int SharedMemory::GetNextImgId() {
        int inx_of_num_img = 0;


        int val = -1;
        {
            bi::scoped_lock<bi::interprocess_mutex> lock(shared_mutexes_->img_id_process_mutex);

            val = (*shared_vec_)[inx_of_num_img];

            (*shared_vec_)[inx_of_num_img]--;
        }

        std::string msg = "GetImgIdToSave val is " + std::to_string(val);

        std::cout << msg << std::endl;

        return val;
    }



    int SharedMemory::GetImgIdToSave() {
        int inx_of_last_save_img_id = 2;

        int id_to_return = -1;

        {// lock the mutex of last save img id.
            bi::scoped_lock<bi::interprocess_mutex> lock(shared_mutexes_->last_save_img_id_mutex);

            id_to_return = ++(*shared_vec_)[inx_of_last_save_img_id];

        }// ulock the mutex

        std::string msg = "id_to_return = " + std::to_string(id_to_return);

        std::cout << msg << std::endl;

        return id_to_return;
    }

}