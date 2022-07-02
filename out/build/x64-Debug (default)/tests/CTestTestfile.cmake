# CMake generated Testfile for 
# Source directory: C:/Users/josef/source/repos/ImgProcess/tests
# Build directory: C:/Users/josef/source/repos/ImgProcess/out/build/x64-Debug (default)/tests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(app_gtests "app_test")
set_tests_properties(app_gtests PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/josef/source/repos/ImgProcess/tests/CMakeLists.txt;25;add_test;C:/Users/josef/source/repos/ImgProcess/tests/CMakeLists.txt;0;")
subdirs("../_deps/googletest-build")
