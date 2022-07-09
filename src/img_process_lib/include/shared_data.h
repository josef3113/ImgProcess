#pragma once
#include <string>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/allocators/allocator.hpp>


namespace bi = boost::interprocess;

namespace img_process {

    using ShmemAllocator = bi::allocator<int, bi::managed_shared_memory::segment_manager>;

    using SharedVector = std::vector<int, ShmemAllocator>;


    struct SharedMutexes
    {
        boost::interprocess::interprocess_mutex img_id_process_mutex;
        
        boost::interprocess::interprocess_mutex last_save_img_id_mutex;
    };
}

