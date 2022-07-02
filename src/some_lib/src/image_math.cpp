#include "image_math.h"


namespace some_lib {

	std::vector<int> ImageMath::Dot(Image img,
									int num_to_multilpy,
									std::vector<int> multiply)
	{
		// check the dimentetion is valid.
		Validation(img, num_to_multilpy, multiply);

		std::vector<int> vec_result;

		for (const auto& row : img) {

			int result = 0;

			for (int i = 0; i < num_to_multilpy; i++) {
				result += row.at(i) * multiply.at(i);
			}

			vec_result.push_back(result);
		}

		return vec_result;
	}



	void ImageMath::Validation(Image img,
							   int num_to_multilpy,
							   std::vector<int> multiply)
	{

		if (img.at(0).size() < num_to_multilpy) {
			throw std::runtime_error("dimension of image smaller than multiply that request");
		}

		if (num_to_multilpy != multiply.size()) {
			throw std::runtime_error("dimension that request and size of multiply not equals");
		}

		int num_of_col = img.at(0).size();
		for (const auto& row : img) {

			if (row.size() != num_of_col)
			{
				throw std::runtime_error("diff size between img rows");
			}
		}
	}
}
