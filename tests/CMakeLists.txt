include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)
FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

add_executable(app_test 
some_lib_test.cpp
time_measure_test.cpp 
image_math_test.cpp 
multi_thread_processor_test.cpp 
x_on_image_test.cpp)


target_link_libraries(app_test
 PRIVATE
  GTest::GTest
  some_lib)

add_test(app_gtests app_test)
