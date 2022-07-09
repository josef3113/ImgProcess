#include "mp_imgs_processor.h"
#include "multi_process_processor.h"



namespace img_process {

    MPImagesProcessor::MPImagesProcessor(int num_of_processes)
        :num_of_processes_{ num_of_processes }
    {}



    void MPImagesProcessor::ProcessImages(int num_of_images) const
    {
        //todo need to create shared memory of int that children (img_process_exe.exe) use to choose img id.

        MultiProcessProcessor processor;

        processor.Process(num_of_processes_, "img_process_exe.exe");
    }
}
