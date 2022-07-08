#include <gtest/gtest.h>
#include "images_processor.h"


TEST(ImagesProcessorTest, basic_test)
{
	int num_of_thread = 10;
	some_lib::ImagesProcessor processor{ num_of_thread };

	int num_of_imgs = 10;
	EXPECT_NO_THROW(processor.ProcessImages(num_of_imgs, some_lib::ImagesProcessor::Folders{}));
}