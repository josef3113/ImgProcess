#include "mp_black_white_img.h"
#include <iostream>
#include "shared_data.h"
#include <boost/filesystem.hpp>



int main()
{
    namespace bi = boost::interprocess;


    // take vector and mutexes from shared memory.
    //Open already created shared memory object.
    bi::shared_memory_object shm(bi::open_only, "MutexMemory", bi::read_write);

    //Map the whole shared memory in this process
    bi::mapped_region region(shm, bi::read_write);
    img_process::SharedMutexes* shared_mutexes = (img_process::SharedMutexes*)region.get_address();


    bi::managed_shared_memory segment(bi::open_only,
                                      "VectorMemory");  //segment name

    img_process::SharedVector* shared_vec = 
                            segment.find<img_process::SharedVector>("SharedVector").first;
    // end taking data from shared memory.

    img_process::SharedMemory shared_memory{ shared_mutexes, shared_vec };

    boost::filesystem::create_directory("output_app");

    int num_processors = shared_memory.GetNumProcesses();

    std::string output_folder_name = "output_app/output"
                                     + std::to_string(num_processors) 
                                     + "processes";

    int next_img_id = shared_memory.GetNextImgId();

    while (next_img_id >= 1)
    {
        std::string input_folder = "data";

        std::string img_name = std::to_string(next_img_id) + ".JPG";

        img_process::MPBlackWhiteImg bw_img(input_folder,
                                            output_folder_name,
                                            img_name,
                                            shared_memory);

        bw_img.Process();

        next_img_id = shared_memory.GetNextImgId();
    }
    return 0;
}