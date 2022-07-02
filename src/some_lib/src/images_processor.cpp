#include "images_processor.h"
#include "multi_thread_processor.h"
#include <iostream>
#include "x_on_image.h"



namespace some_lib {

	ImagesProcessor::ImagesProcessor(int num_of_threads)
		:num_of_threads_{ num_of_threads }
		,image_id_to_process_{ 0 }
		,num_of_images_{ 0 }
	{}



	void ImagesProcessor::ProcessImages(int num_of_images, std::string folder_path) {

		num_of_images_ = num_of_images;

		MultiThreadProcessor<std::string> processor;

		auto mission = [this, folder_path](std::string) { ProcessImage(folder_path); };

		MultiThreadProcessor<std::string>::Task task{ folder_path, mission  };

		processor.Process(num_of_threads_, task);
	}


	int ImagesProcessor::GetNextImgIdToProcess() {

		int current_image_id = -1;

		{// lock when take img_id to process
			std::lock_guard lg(mtx_);
			if (image_id_to_process_ < num_of_images_) {
				current_image_id = image_id_to_process_++;
			}
		}// unlock

		return current_image_id;
	}



	void ImagesProcessor::ProcessImage(std::string folder_path) {

		std::cout << "ProcessImage " << std::endl;
		int image_id = GetNextImgIdToProcess();

		while ((image_id != -1) && (image_id < num_of_images_)) {

			// read and do somting on image num image_id
			XOnImage{ folder_path, image_id };

			image_id = GetNextImgIdToProcess();
		}
	}
}
