#pragma once
#include "folders.h"


namespace img_process {

    // multi process imgs processor.
    class MPImagesProcessor {
    public:

        MPImagesProcessor(int num_of_processes);

        void ProcessImages(int num_of_images);

    private:
        int num_of_processes_;
    };
}