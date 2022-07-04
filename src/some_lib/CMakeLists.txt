
set(BOOST_ROOT "C://boost_1_66_0//boost_1_66_0")

find_package(Boost 1.36.0)
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
  message("//////////////// Boost Found")
endif()

set(OpenCV_DIR "C://opencv//build")

find_package(OpenCV REQUIRED )





add_library(some_lib 
"src/time_measure.cpp" 
"src/image_math.cpp" 
"src/x_on_image.cpp"
"src/images_processor.cpp"
)

target_include_directories(some_lib PUBLIC ${OpenCV_INCLUDE_DIRS} )
target_link_libraries(some_lib PUBLIC ${OpenCV_LIBS} )

target_include_directories(some_lib PUBLIC include ${Boost_INCLUDE_DIRS})