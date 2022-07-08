#include <opencv2/core.hpp> // check why boost fail without this.
#include <iostream>
#include "boost/process.hpp"
#include "time_measure.h"
#include "images_processor.h"



int main()
{
    // ------------------- multi process code
    // todo wrap this code on class MultiProcessImgsProcessor.
	namespace bp = boost::process;

    int num_of_processes = 10;
    std::vector<bp::child> processes;

    for (int i = 0; i < num_of_processes; i++) {
        processes.push_back(bp::child("img_process.exe"));
    }

    for (auto& process : processes) {
        if (process.joinable()) {
            std::cout << "process.joinable()" << std::endl;

            process.join();
        }
    }
    // end of multi process.


	// --------------- multi thread code ------
    utilities::TimeMeasur timer;

	std::vector<utilities::TimeMeasur::TimeProcess> times_process;

	int max_num_worker = 9;
	for (int i = 1; i <= max_num_worker; i++) {

		timer.Start();

		int worker_num = i;
		some_lib::ImagesProcessor img_processor{ worker_num };

		int image_count = 10;
		some_lib::ImagesProcessor::Folders folders;
		img_processor.ProcessImages(image_count, folders);

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
	// end multi thread code.

	int a = 0;
	std::cin >> a;
}