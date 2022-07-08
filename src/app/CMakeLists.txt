add_executable(app_exe main.cpp)

target_link_libraries(
	app_exe
	PUBLIC
	img_process_lib
)