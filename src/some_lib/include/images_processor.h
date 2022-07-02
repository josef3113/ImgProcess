#pragma once
#include <string>
#include <mutex>


namespace some_lib {

	class ImagesProcessor {

	public:
		ImagesProcessor(int num_of_threads);

		void ProcessImages(int num_of_images, std::string folder_path);

	private:

		int GetNextImgIdToProcess();

		void ProcessImage(std::string folder_path);

		std::mutex mtx_;

		int image_id_to_process_;

		int num_of_threads_;

		int num_of_images_;
	};
}