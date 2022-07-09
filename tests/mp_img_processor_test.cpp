#include <gtest/gtest.h>
#include "mp_imgs_processor.h"



TEST(MPImagesProcessorTest, basic_test)
{
    int num_process = 2;
    
    img_process::MPImagesProcessor  p{ 2 };

    std::string exe_path = "img_process_exe.exe";

    int num_of_imgs = 10;

    EXPECT_NO_THROW(p.ProcessImages(num_of_imgs));
}
