#include <iostream>
#include "time_measure.h"
#include "mt_imgs_processor.h"
#include "mp_imgs_processor.h"
#include <vector>
#include <boost/filesystem.hpp>



using ProcessingTimes = std::vector<utilities::TimeMeasur::TimeProcess>;

ProcessingTimes RunMultiThread();

ProcessingTimes RunMultiProcess();

void Summary(const ProcessingTimes& mt_processing_times,
             const ProcessingTimes& mp_processing_times);


int main()
{
    auto multi_process_times = RunMultiProcess();

    auto multi_thread_times = RunMultiThread();

    Summary(multi_thread_times, multi_process_times);

    int a = 0;
    std::cin >> a;
}



ProcessingTimes RunMultiThread()
{
    utilities::TimeMeasur timer;

    std::vector<utilities::TimeMeasur::TimeProcess> times_process;

    int max_num_worker = 9;
    for (int i = 1; i <= max_num_worker; i++) {

        timer.Start();

        int worker_num = i;
        img_process::MTImagesProcessor img_processor{ worker_num };

        int image_count = 10;
        img_process::Folders folders;
        folders.input_folder_name_ = "data";

        boost::filesystem::create_directory("output_app");

        folders.output_folder_name_ = "output_app/output" +
                                        std::to_string(worker_num) +
                                        "worker";

        img_processor.ProcessImages(image_count, folders);

        timer.Stop();

        times_process.push_back(utilities::TimeMeasur::TimeProcess{ i, timer.GetTime().count() });

        timer.Reset();
    }

    return times_process;
}



ProcessingTimes RunMultiProcess()
{
    utilities::TimeMeasur timer;

    std::vector<utilities::TimeMeasur::TimeProcess> times_process;

    // current code not supporting multi process.
    int max_num_worker = 0;
    for (int i = 1; i <= max_num_worker; i++) {

        timer.Start();

        int worker_num = i;
        img_process::MPImagesProcessor img_processor{ worker_num };

        int image_count = 10;

        img_processor.ProcessImages(image_count);

        timer.Stop();

        times_process.push_back(utilities::TimeMeasur::TimeProcess{ i, timer.GetTime().count() });

        timer.Reset();
    }

    return times_process;
}



void Summary(const ProcessingTimes& mt_processing_times,
             const ProcessingTimes& mp_processing_times)
{
    std::cout << "\n summary app \n\n" << std::endl;

    for (const auto& time : mt_processing_times) {

        int num_worker = std::get<int>(time);
        auto time_mesure = std::get<std::chrono::nanoseconds>(time);

        std::cout << "num of threads " << num_worker
            << " take " << time_mesure.count() << "[nano sec]" << std::endl;
    }

    std::cout << std::endl;

    for (const auto& time : mp_processing_times) {

        int num_worker = std::get<int>(time);
        auto time_mesure = std::get<std::chrono::nanoseconds>(time);

        std::cout << "num of processes " << num_worker
            << " take " << time_mesure.count() << "[nano sec]" << std::endl;
    }

}