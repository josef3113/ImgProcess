#pragma once
#include "folders.h"



namespace img_process {

    // multi process imgs processor.
    class MPImagesProcessor {
    public:
        MPImagesProcessor(int num_of_processes);
        
        ~MPImagesProcessor();

        void ProcessImages(int num_of_images) const;

    private:
        void CreateSharedData(int num_of_imgs) const;

        int num_of_processes_;
    };
}