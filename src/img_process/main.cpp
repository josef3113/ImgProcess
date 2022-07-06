#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "x_on_image.h"



using namespace cv;



int main()
{
    // todo - need to include shared-memory / semaphore that get img_id process safe.
    // 1 - take img_id to process - lock the process.
    // 2 - process the img that load.
    // 3 - save result 

    // this function - will be execute 2,3.
    some_lib::XOnImage("empty", 1);


    // current show img.
    std::string image_path = samples::findFile("starry_night.jpg");;
    Mat img = imread(image_path, IMREAD_COLOR);
    if(img.empty())
    {
        std::cout << "Could not read the image: " << image_path << std::endl;
        return 1;
    }
    imshow("Display window", img);
    int k = waitKey(0); // Wait for a keystroke in the window
    if(k == 's')
    {
        imwrite("starry_night.png", img);
    }
    return 0;
}