#pragma once
#include <string>
#include <mutex>
#include "folders.h"



namespace img_process {

    // multi thread imgs processor.
    class MTImagesProcessor {
    public:
        MTImagesProcessor(int num_of_threads);

        void ProcessImages(int num_of_images, const Folders& folders_path);

    private:
        int GetNextImgIdToProcess();

        void ProcessImage(const Folders& folders_path);

        std::mutex mtx_;

        int image_id_to_process_;

        int num_of_threads_;

        int num_of_images_;
    };
}