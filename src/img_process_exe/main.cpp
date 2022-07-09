#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "mp_black_white_img.h"
#include <iostream>
#include "shared_data.h"
#include <boost/filesystem.hpp>



using namespace cv;






int main()
{
    namespace bi = boost::interprocess;

    std::string msg = "in child pid" + std::to_string(getpid());

    //Open already created shared memory object.
    bi::shared_memory_object shm(bi::open_only, "MutexMemory", bi::read_write);

    //Map the whole shared memory in this process
    bi::mapped_region region(shm, bi::read_write);
    img_process::SharedMutexes* shared_mutexes = (img_process::SharedMutexes*)region.get_address();


    bi::managed_shared_memory segment(bi::open_only,
                                      "VectorMemory");  //segment name

    img_process::SharedVector* shared_vec = 
                            segment.find<img_process::SharedVector>("SharedVector").first;

    boost::filesystem::create_directory("output_app");

    int inx_of_num_img = 0;
    int inx_of_num_processers = 1;
    int inx_of_last_save_img_id = 2;

    int num_processors = (*shared_vec)[inx_of_num_processers];

    std::string output_folder_name = "output_app/output"
                                     + std::to_string(num_processors) 
                                     + "processes";

    int val = -1;
    {
        bi::scoped_lock<bi::interprocess_mutex> lock(shared_mutexes->img_id_process_mutex);

        val = (*shared_vec)[inx_of_num_img];

        (*shared_vec)[inx_of_num_img]--;
    }

    while (val >= 1)
    {
        std::string input_folder = "data";

        std::string img_name = std::to_string(val) + ".JPG";

        // process the img id that get.
        img_process::MPBlackWhiteImg bw_img(input_folder,
                                            output_folder_name,
                                            img_name,
                                            shared_mutexes,
                                            shared_vec);

        bw_img.Process();

        { // try take another img id.
            bi::scoped_lock<bi::interprocess_mutex> lock(shared_mutexes->img_id_process_mutex);
            
            val = (*shared_vec)[inx_of_num_img];

            std::string msg = "val = " + std::to_string(val) +
                "pid " + std::to_string(getpid());

            std::cout << msg << std::endl;
            
            (*shared_vec)[inx_of_num_img]--;
        }
    }
    return 0;
}