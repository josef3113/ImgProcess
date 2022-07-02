#include <iostream>
#include "time_measure.h"
#include "images_processor.h"
#include <vector>

int main() {

	utilities::TimeMeasur timer;

	std::vector<utilities::TimeMeasur::TimeProcess> times_process;

	int max_num_worker = 9;
	for (int i = 1; i <= max_num_worker; i++) {

		timer.Start();

		int worker_num = i;
		some_lib::ImagesProcessor img_processor{ worker_num };

		int image_count = 10;
		img_processor.ProcessImages(image_count, "empty");

		timer.Stop();

		times_process.push_back(utilities::TimeMeasur::TimeProcess{ i, timer.GetTime().count() });

		timer.Reset();
	}



	std::cout << "summary app \n\n" << std::endl;

	for (const auto& time : times_process) {

		int num_worker = std::get<int>(time);
		auto time_mesure = std::get<std::chrono::nanoseconds>(time);

		std::cout << "num of worker " << num_worker
			<< "take " << time_mesure.count() << "[nano sec]" << std::endl;
	}
}