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

    // wait for input from user.
    int a = 0;
    std::cin >> a;
}



ProcessingTimes RunMultiThread()
{
    utilities::TimeMeasur timer;

    std::vector<utilities::TimeMeasur::TimeProcess> times_process;

    int max_num_workers = 9;
    for (int i = 1; i <= max_num_workers; i++) {

        timer.Start();

        int workers_count = i;
        img_process::MTImagesProcessor img_processor{ workers_count };

        int images_count = 10;

        boost::filesystem::create_directory("output_app");
        
        img_process::Folders folders;
        folders.input_folder_name_ = "data";
        folders.output_folder_name_ = "output_app/output" +
                                        std::to_string(workers_count) +
                                        "thread";

        img_processor.ProcessImages(images_count, folders);

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

    int max_num_worker = 9;
    for (int i = 1; i <= max_num_worker; i++) {

        timer.Start();

        int workers_count = i;
        img_process::MPImagesProcessor img_processor{ workers_count };

        int images_count = 10;

        img_processor.ProcessImages(images_count);

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

        int workers_count = std::get<int>(time);
        auto time_mesure = std::get<std::chrono::nanoseconds>(time);

        std::cout << "num of threads " << workers_count
            << " take " << time_mesure.count() << "[nano sec]" << std::endl;
    }

    std::cout << std::endl;

    for (const auto& time : mp_processing_times) {

        int workers_count = std::get<int>(time);
        auto time_mesure = std::get<std::chrono::nanoseconds>(time);

        std::cout << "num of processes " << workers_count
            << " take " << time_mesure.count() << "[nano sec]" << std::endl;
    }

}