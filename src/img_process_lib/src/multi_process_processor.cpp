#include "multi_process_processor.h"



namespace img_process {

    void MultiProcessProcessor::Process(int num_of_process, 
                                        const std::string& exe_path) const
    {
        std::cout << "Process ..." << std::endl;

        std::vector<boost::process::child> processes;

        for (int i = 0; i < num_of_process; i++) {
            processes.push_back(boost::process::child(exe_path));
        }

        for (auto& process : processes) {
            if (process.joinable()) {

                std::string msg = std::to_string(process.id()) + "joinable ";
                std::cout << msg << std::endl;

                process.join();
            }
        }

        std::cout << "Process Done." << std::endl;
    }
}