#include <gtest/gtest.h>
#include "multi_process_processor.h"



TEST(MultiProcessProcessorTest, basic_test)
{
    img_process::MultiProcessProcessor  p;

    int num_process = 2;

    std::string exe_path = "sample_exe.exe";

    EXPECT_NO_THROW(p.Process(num_process, exe_path));
}
