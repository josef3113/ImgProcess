#include <gtest/gtest.h>
#include "multi_thread_processor.h"



TEST(MultiThreadProcessorTest, basic_test)
{
    some_lib::MultiThreadProcessor <std::string> p;

    int num_threads = 2;

    std::string msg_to_print = "hello from tests";

    auto mission = [msg_to_print](std::string) { std::cout << msg_to_print << std::endl; };

    some_lib::MultiThreadProcessor<std::string>::Task task{ msg_to_print, mission };

    EXPECT_NO_THROW(p.Process(num_threads, task));
}