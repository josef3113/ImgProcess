#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "black_white_img.h"
#include <iostream>



using namespace cv;



int main()
{
    // todo - need to include shared-memory / semaphore that get img_id process safe.
    // 1 - take img_id to process - lock the process.
    // 2 - process the img that load.
    // 3 - save result 

    // this function - will be execute 2,3.
    //img_process::BlackWhiteImg img1("empty", "empty", std::to_string(1));

    std::string msg = "process id " + std::to_string( getpid());

    std::cout << msg << std::endl;

    return 0;
}