#pragma once
#include <thread>
#include <functional>
#include <iostream>



namespace img_process {

    template <typename Type>
    class MultiThreadProcessor {
    public:
        using Function = std::function<void(Type)>;
        using Task = std::tuple<Type, Function>;


        void Process(int num_of_threads, const Task& task) {
            std::cout << "Process ..." << std::endl;

            task_ = task;

            std::vector<std::thread> workers;

            for (int i = 0; i < num_of_threads; i++) {
                workers.push_back(std::thread{ std::bind(&MultiThreadProcessor<Type>::Do,this) });
            }

            // wait that all tasks will be done.
            for (auto& thread : workers) {
                if (thread.joinable()) {
                    thread.join();
                }
            }

            std::cout << "Process Done." << std::endl;
        }

    private:
        // apply the mission that get.
        void Do() const {
            Type arg = std::get<Type>(task_);
            auto mission = std::get<Function>(task_);

            mission(arg);
        }

        MultiThreadProcessor<Type>::Task task_;
    };
}
