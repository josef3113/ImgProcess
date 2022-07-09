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
time_measure_test.cpp 
multi_thread_processor_test.cpp 
black_white_img_test.cpp 
mt_imgs_processor_test.cpp
multi_process_processor_test.cpp
mp_img_processor_test.cpp)


target_link_libraries(app_test
 PRIVATE
  GTest::GTest
  img_process_lib)

add_test(app_gtests app_test)


########### create sample exe for testing
add_executable(sample_exe sample_exe.cpp)
#########################################