#pragma once
#include <string>
#include <mutex>


namespace img_process {

    class ImagesProcessor {
    public:

        struct Folders {
            std::string input_folder_name_{ "empty path" };
            std::string output_folder_name_{ "empty path" };
        };


        ImagesProcessor(int num_of_threads);

        void ProcessImages(int num_of_images, Folders folders_path);

    private:

        int GetNextImgIdToProcess();

        void ProcessImage(Folders folders_path);

        std::mutex mtx_;

        int image_id_to_process_;

        int num_of_threads_;

        int num_of_images_;
    };
}