#include "mp_imgs_processor.h"
#include "multi_process_processor.h"
#include "shared_data.h"



namespace img_process {

    MPImagesProcessor::MPImagesProcessor(int num_of_processes)
        :num_of_processes_{ num_of_processes }
    {}



    MPImagesProcessor::~MPImagesProcessor()
    {
        bi::shared_memory_object::remove("MutexMemory");

        bi::shared_memory_object::remove("VectorMemory");
    }



    void MPImagesProcessor::ProcessImages(int num_of_images) const
    {
        CreateSharedData(num_of_images);

        MultiProcessProcessor processor;

        processor.Process(num_of_processes_, "img_process_exe.exe");
    }



    void MPImagesProcessor::CreateSharedData(int num_of_imgs) const
    {
        // --------------- create shared memory for children
        bi::shared_memory_object::remove("VectorMemory");

        bi::managed_shared_memory segment(bi::create_only,
                                          "VectorMemory", //segment name
                                          65536);          //segment size in bytes

        const ShmemAllocator alloc_inst(segment.get_segment_manager());

        SharedVector* shared_vec = segment.construct<SharedVector>("SharedVector") //object name
                                   (alloc_inst);//first ctor parameter

        // ------------ create shared mutexs
        bi::shared_memory_object::remove("MutexMemory");

        bi::shared_memory_object shm(bi::create_only,
                                     "MutexMemory",
                                     bi::read_write);

        shm.truncate(1000);

        bi::mapped_region region(shm, bi::read_write);
        void* addr = region.get_address();
        //----------------------------

        // the first element in vector is number of imgs.
        shared_vec->push_back(num_of_imgs);

        // the seconed element in vector is number of process.
        shared_vec->push_back(num_of_processes_);

        // the third element in vector is the last img id that saved.
        shared_vec->push_back(0);
    }
}
