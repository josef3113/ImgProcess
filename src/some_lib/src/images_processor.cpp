#include "images_processor.h"
#include "multi_thread_processor.h"
#include <iostream>
#include "bw_image.h"



namespace some_lib {

	ImagesProcessor::ImagesProcessor(int num_of_threads)
		:num_of_threads_{ num_of_threads }
		,image_id_to_process_{ 0 }
		,num_of_images_{ 0 }
	{}



	void ImagesProcessor::ProcessImages(int num_of_images, Folders folders_path) {

		num_of_images_ = num_of_images;

		MultiThreadProcessor<Folders> processor;

		auto mission = [this, folders_path](Folders) { ProcessImage(folders_path); };

		MultiThreadProcessor<Folders>::Task task{ folders_path, mission  };

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



	void ImagesProcessor::ProcessImage(Folders folders_path) {

		std::cout << "ProcessImage " << std::endl;
		int image_id = GetNextImgIdToProcess();

		while ((image_id != -1) && (image_id < num_of_images_)) {

			// read and do somting on image num image_id
			BwImage{ folders_path.input_folder_name_,
					folders_path.output_folder_name_ ,
					std::to_string(image_id )+ ".JPG"};

			image_id = GetNextImgIdToProcess();
		}
	}
}