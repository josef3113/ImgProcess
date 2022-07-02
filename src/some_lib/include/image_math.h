#pragma once 
#include <vector>
#include <stdexcept>



namespace some_lib {

	using Image = std::vector<std::vector<int>>;

	class  ImageMath
	{
	public:

		std::vector<int> Dot(Image img,
							 int num_to_multilpy,
							 std::vector<int> multiply);

	private:

		void Validation(Image img,
						int num_to_multilpy,
						std::vector<int> multiply);
	};
}