#include "mp_imgs_processor.h"
#include "multi_process_processor.h"
#include "shared_data.h"



namespace img_process {

    MPImagesProcessor::MPImagesProcessor(int num_of_processes)
        :num_of_processes_{ num_of_processes }
    {
        //Remove shared memory on construction
        struct shm_remove
        {
            shm_remove() { bi::shared_memory_object::remove("MutexMemory"); }
            ~shm_remove() { bi::shared_memory_object::remove("MutexMemory"); }
        } remover;
    }



    MPImagesProcessor::~MPImagesProcessor()
    {
        //Remove shared memory on destruction
        struct shm_remove
        {
            shm_remove() { bi::shared_memory_object::remove("MutexMemory"); }
            ~shm_remove() { bi::shared_memory_object::remove("MutexMemory"); }
        } remover;
    }



    void MPImagesProcessor::ProcessImages(int num_of_images) const
    {
        CreateSharedDate(num_of_images);

        MultiProcessProcessor processor;

        processor.Process(num_of_processes_, "img_process_exe.exe");
    }



    void MPImagesProcessor::CreateSharedDate(int num_of_imgs) 
    {
        // --------------- create shared memory for children
        std::cout << "In parent" << std::endl;

        bi::shared_memory_object::remove("VectorMemory");

        bi::managed_shared_memory segment(bi::create_only,
                                          "VectorMemory", //segment name
                                          65536);          //segment size in bytes


        const ShmemAllocator alloc_inst(segment.get_segment_manager());

        bi::shared_memory_object shm(bi::create_only,
                                     "MutexMemory",
                                     bi::read_write);


        SharedVector* shared_vec = segment.construct<SharedVector>("SharedVector") //object name
                                   (alloc_inst);//first ctor parameter

        shm.truncate(1000);

        bi::mapped_region region(shm, bi::read_write);
        void* addr = region.get_address();
        SharedMutexes* mutexes = new (addr) SharedMutexes();

        // the first element in vector is number of imgs.
        shared_vec->push_back(num_of_imgs);

        // the seconed element in vector is number of process.
        shared_vec->push_back(num_of_processes_);

        // the third element in vector is the last img id that saved.
        shared_vec->push_back(0);

    }
}
