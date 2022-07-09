#include <gtest/gtest.h>
#include "mp_imgs_processor.h"



TEST(MPImagesProcessorTest, basic_test)
{
    int processes_count = 1;
    
    img_process::MPImagesProcessor  p{ processes_count };

    std::string exe_path = "img_process_exe.exe";

    int imgs_count = 10;

    EXPECT_NO_THROW(p.ProcessImages(imgs_count));
}
