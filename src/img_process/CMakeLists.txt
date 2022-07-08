add_executable(img_process_exe main.cpp)

target_link_libraries(
	img_process_exe
	PUBLIC
	img_process_lib
)