#pragma once
#include <vector>
#include <algorithm> // for boost process.hpp
#include "boost/process.hpp"
#include <iostream>



namespace img_process {

    class MultiProcessProcessor {
    public:
        void Process(int num_of_process, const std::string& exe_path) const;
    };
}
