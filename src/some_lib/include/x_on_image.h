#pragma once
#include <mutex>
#include <iostream>
#include "image_math.h"



namespace some_lib {

	// class the get id of image,load the img ,do somting and save the result.
	class XOnImage {
	public:
		XOnImage(std::string folder_path, int img_id); 

	private:
		std::mutex print_mtx_;
		
		std::mutex increment_id_mtx_;

		static int last_save_img_;
	};
}
