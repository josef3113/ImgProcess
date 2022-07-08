add_library(some_lib 
"src/time_measure.cpp" 
"src/image_math.cpp" 
"src/bw_image.cpp"
"src/images_processor.cpp"
)



################# include boost lib ###################
add_definitions(${Boost_LIB_DIAGNOSTIC_DEFINITIONS})
set(BOOST_ROOT "C://boost_1_77_0//boost_1_77_0")

set(Boost_USE_STATIC_LIBS        ON)  # only find static libs
set(Boost_USE_DEBUG_LIBS        ON) 
set(Boost_USE_RELEASE_LIBS       ON)  # only find release libs
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
find_package(Boost 1.77.0 COMPONENTS filesystem)
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
	message("boost found Boost 1.77.0 COMPONENTS filesystem")
endif()

target_include_directories(some_lib PUBLIC include ${Boost_INCLUDE_DIRS})
target_link_libraries(some_lib PUBLIC Boost::filesystem )
#########################################################



######################## include opencv lib ##############
set(OpenCV_DIR "C://opencv//build")

find_package(OpenCV REQUIRED )

target_include_directories(some_lib PUBLIC ${OpenCV_INCLUDE_DIRS} )
target_link_libraries(some_lib PUBLIC ${OpenCV_LIBS} )
##########################################################