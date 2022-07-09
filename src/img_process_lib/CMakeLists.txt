set(NAME_LIB img_process_lib)

add_library(${NAME_LIB}
"src/time_measure.cpp" 
"src/convert_img.cpp" 
"src/black_white_img.cpp"
"src/mt_imgs_processor.cpp"
"src/mp_imgs_processor.cpp" 
"src/mp_black_white_img.cpp"  
"src/shared_data.cpp")



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

target_include_directories(${NAME_LIB} PUBLIC include ${Boost_INCLUDE_DIRS})
target_link_libraries(${NAME_LIB} PUBLIC Boost::filesystem )
#########################################################



######################## include opencv lib ##############
set(OpenCV_DIR "C://opencv//build")

find_package(OpenCV REQUIRED )

target_include_directories(${NAME_LIB} PUBLIC ${OpenCV_INCLUDE_DIRS} )
target_link_libraries(${NAME_LIB} PUBLIC ${OpenCV_LIBS} )
##########################################################