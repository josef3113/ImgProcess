add_library(some_lib 
"src/time_measure.cpp" 
"src/image_math.cpp" 
"src/x_on_image.cpp"
"src/images_processor.cpp"
)

target_include_directories(some_lib PUBLIC include)