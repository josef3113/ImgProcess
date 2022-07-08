#pragma once
#include <thread>
#include <functional>
#include <iostream>



namespace img_process {

    template <typename T>
    class MultiThreadProcessor {
    public:
        using Type = T;
        using Function = std::function<void(Type)>;
        using Task = std::tuple<T, Function>;


        void Process(int num_of_threads, Task task) {
            std::cout << "Process ..." << std::endl;

            task_ = task;

            std::vector<std::thread> workers;

            for (int i = 0; i < num_of_threads; i++) {
                workers.push_back(std::thread{ std::bind(&MultiThreadProcessor<T>::Do,this) });
            }

            // wait that all tasks will be done.
            for (auto& t : workers) {
                if (t.joinable()) {
                    t.join();
                }
            }

            std::cout << "Process Done." << std::endl;
        }

    private:

        // apply the mission that get.
        void Do() {
            T arg = std::get<T>(task_);
            auto mission = std::get<Function>(task_);

            mission(arg);
        }

        MultiThreadProcessor<T>::Task task_;
    };
}
