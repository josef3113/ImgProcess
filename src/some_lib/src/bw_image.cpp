#pragma once
#include "bw_image.h"
#include <boost/filesystem.hpp>


namespace some_lib {
	int BwImage::last_save_img_ = 0;

	cv::Mat ConvertBGRtoBW::Convert(const cv::Mat& origin_img,
									ConvertBGRtoBW::BGRMultipliers multipliers)
	{
		cv::Mat img_res(origin_img.rows, origin_img.cols, 1);

		for (int i = 0; i < origin_img.rows; i++) {
			for (int j = 0; j < origin_img.cols; j++) {

				int sum = origin_img.at<cv::Vec3b>(i, j)[0] * multipliers.b_multipler_;
				sum += origin_img.at<cv::Vec3b>(i, j)[1] * multipliers.g_multipler_;
				sum += origin_img.at<cv::Vec3b>(i, j)[2] * multipliers.r_multiple_;

				img_res.at<uchar>(i, j) = sum;
			}
		}

		return img_res;
	}



	BwImage::BwImage(std::string input_folder_path,
					std::string output_folder_path,
					std::string img_name) {

		// read imag 
		//ReadImg(input_folder_path, img_name);

		// converct img to black & white.
		// img_ = ConvertBGRtoBW::Convert(img_, multipliers_);

		// save image
		//SaveImg(output_folder_path);
	}



	void BwImage::ReadImg(std::string folder_name, std::string img_name) {

		std::string img_path = folder_name + "/" + img_name;
		img_ = cv::imread(img_path, cv::IMREAD_COLOR);

		if (img_.empty()) {
			throw std::runtime_error("cannot read img " + img_path);
		}
	}


	bool BwImage::SaveImg( std::string out_folder_name) {

		int save_id = -1;
		{// lock when take the id of img that save.
			std::lock_guard lg(increment_id_mtx_);
			save_id = last_save_img_++;
		}// unlock

		boost::filesystem::create_directory(out_folder_name);

		std::string save_path = out_folder_name + "/"
								+ std::to_string(save_id) + ".png";

		return cv::imwrite(save_path, img_);
	}
}
