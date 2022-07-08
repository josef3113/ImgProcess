#pragma once
#include <mutex>
#include <iostream>
#include "image_math.h"
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>



namespace some_lib {

	class ConvertBGRtoBW {
	public:
		struct BGRMultipliers {

			BGRMultipliers(float b_multipler,
							float g_multipler,
							float r_multiple_)
				: b_multipler_{ b_multipler }
				, g_multipler_{ g_multipler }
				, r_multiple_{ r_multiple_ }{}

			float b_multipler_;

			float g_multipler_;

			float r_multiple_;
		};

		static cv::Mat Convert( const cv::Mat& origin_img,
								ConvertBGRtoBW::BGRMultipliers multipliers);
	};



	// class the get path and name of image,load the img ,convert to black/white and save the result.
	class BwImage {
	public:
		BwImage(std::string input_folder_path,
				std::string output_folder_path ,
				std::string img_name);

	private:

		void ReadImg(std::string folder_name, std::string img_name);
		
		bool SaveImg(std::string folder_name);
		
		std::mutex increment_id_mtx_;

		static int last_save_img_;

		cv::Mat img_;

		ConvertBGRtoBW::BGRMultipliers multipliers_{ 0.299,0.587,0.114 };
	};
}
