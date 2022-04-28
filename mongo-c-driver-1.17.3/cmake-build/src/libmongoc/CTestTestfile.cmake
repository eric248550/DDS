# CMake generated Testfile for 
# Source directory: /home/xinxing06/DDS/mongo-c-driver-1.17.3/src/libmongoc
# Build directory: /home/xinxing06/DDS/mongo-c-driver-1.17.3/cmake-build/src/libmongoc
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(test-libmongoc "/home/xinxing06/DDS/mongo-c-driver-1.17.3/cmake-build/src/libmongoc/test-libmongoc")
set_tests_properties(test-libmongoc PROPERTIES  WORKING_DIRECTORY "/home/xinxing06/DDS/mongo-c-driver-1.17.3/src/libmongoc/../..")
subdirs("build")
subdirs("examples")
subdirs("src")
subdirs("tests")
