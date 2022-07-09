#include <gtest/gtest.h>
#include "mt_imgs_processor.h"



TEST(MTImagesProcessorTest, basic_test)
{
    int num_of_thread = 10;
    img_process::MTImagesProcessor processor{ num_of_thread };

    int num_of_imgs = 10;

    img_process::Folders folders;
    folders.input_folder_name_ = "data";
    folders.output_folder_name_ = "output test";

    EXPECT_NO_THROW(processor.ProcessImages(num_of_imgs, folders));
}