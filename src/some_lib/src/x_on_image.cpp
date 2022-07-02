#pragma once
#include "x_on_image.h"



namespace some_lib {
	int XOnImage::last_save_img_ = 0;

	// todo separate methodes to read process and save img. 
	XOnImage::XOnImage(std::string folder_path, int img_id) {

		// read imag number image_id
		std::this_thread::sleep_for(std::chrono::seconds(1));
		{
			std::lock_guard lg(print_mtx_);
			std::cout << "folder_path = " << folder_path << " process imag num " << img_id << std::endl;
		}

		// process image
		ImageMath calc;
		Image img{ {1,2,3,4},{3,4,6,7} };
		calc.Dot(img, 4, { 1,2,3,4 });

		// save image
		{
			std::lock_guard lg(increment_id_mtx_);
			int save_id = last_save_img_++;

			std::cout << "save " << save_id << "image." << std::endl;
		}
	}
}
