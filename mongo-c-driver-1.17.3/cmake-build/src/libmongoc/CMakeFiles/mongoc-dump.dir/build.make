# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/xinxing06/DDS/mongo-c-driver-1.17.3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/xinxing06/DDS/mongo-c-driver-1.17.3/cmake-build

# Include any dependencies generated for this target.
include src/libmongoc/CMakeFiles/mongoc-dump.dir/depend.make

# Include the progress variables for this target.
include src/libmongoc/CMakeFiles/mongoc-dump.dir/progress.make

# Include the compile flags for this target's objects.
include src/libmongoc/CMakeFiles/mongoc-dump.dir/flags.make

src/libmongoc/CMakeFiles/mongoc-dump.dir/examples/mongoc-dump.c.o: src/libmongoc/CMakeFiles/mongoc-dump.dir/flags.make
src/libmongoc/CMakeFiles/mongoc-dump.dir/examples/mongoc-dump.c.o: ../src/libmongoc/examples/mongoc-dump.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xinxing06/DDS/mongo-c-driver-1.17.3/cmake-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/libmongoc/CMakeFiles/mongoc-dump.dir/examples/mongoc-dump.c.o"
	cd /home/xinxing06/DDS/mongo-c-driver-1.17.3/cmake-build/src/libmongoc && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/mongoc-dump.dir/examples/mongoc-dump.c.o   -c /home/xinxing06/DDS/mongo-c-driver-1.17.3/src/libmongoc/examples/mongoc-dump.c

src/libmongoc/CMakeFiles/mongoc-dump.dir/examples/mongoc-dump.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mongoc-dump.dir/examples/mongoc-dump.c.i"
	cd /home/xinxing06/DDS/mongo-c-driver-1.17.3/cmake-build/src/libmongoc && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/xinxing06/DDS/mongo-c-driver-1.17.3/src/libmongoc/examples/mongoc-dump.c > CMakeFiles/mongoc-dump.dir/examples/mongoc-dump.c.i

src/libmongoc/CMakeFiles/mongoc-dump.dir/examples/mongoc-dump.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mongoc-dump.dir/examples/mongoc-dump.c.s"
	cd /home/xinxing06/DDS/mongo-c-driver-1.17.3/cmake-build/src/libmongoc && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/xinxing06/DDS/mongo-c-driver-1.17.3/src/libmongoc/examples/mongoc-dump.c -o CMakeFiles/mongoc-dump.dir/examples/mongoc-dump.c.s

# Object files for target mongoc-dump
mongoc__dump_OBJECTS = \
"CMakeFiles/mongoc-dump.dir/examples/mongoc-dump.c.o"

# External object files for target mongoc-dump
mongoc__dump_EXTERNAL_OBJECTS =

src/libmongoc/mongoc-dump: src/libmongoc/CMakeFiles/mongoc-dump.dir/examples/mongoc-dump.c.o
src/libmongoc/mongoc-dump: src/libmongoc/CMakeFiles/mongoc-dump.dir/build.make
src/libmongoc/mongoc-dump: src/libmongoc/libmongoc-1.0.so.0.0.0
src/libmongoc/mongoc-dump: /usr/lib/arm-linux-gnueabihf/libsasl2.so
src/libmongoc/mongoc-dump: /usr/lib/arm-linux-gnueabihf/libssl.so
src/libmongoc/mongoc-dump: /usr/lib/arm-linux-gnueabihf/libcrypto.so
src/libmongoc/mongoc-dump: /usr/lib/arm-linux-gnueabihf/libz.so
src/libmongoc/mongoc-dump: src/libbson/libbson-1.0.so.0.0.0
src/libmongoc/mongoc-dump: src/libmongoc/CMakeFiles/mongoc-dump.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/xinxing06/DDS/mongo-c-driver-1.17.3/cmake-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable mongoc-dump"
	cd /home/xinxing06/DDS/mongo-c-driver-1.17.3/cmake-build/src/libmongoc && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mongoc-dump.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/libmongoc/CMakeFiles/mongoc-dump.dir/build: src/libmongoc/mongoc-dump

.PHONY : src/libmongoc/CMakeFiles/mongoc-dump.dir/build

src/libmongoc/CMakeFiles/mongoc-dump.dir/clean:
	cd /home/xinxing06/DDS/mongo-c-driver-1.17.3/cmake-build/src/libmongoc && $(CMAKE_COMMAND) -P CMakeFiles/mongoc-dump.dir/cmake_clean.cmake
.PHONY : src/libmongoc/CMakeFiles/mongoc-dump.dir/clean

src/libmongoc/CMakeFiles/mongoc-dump.dir/depend:
	cd /home/xinxing06/DDS/mongo-c-driver-1.17.3/cmake-build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/xinxing06/DDS/mongo-c-driver-1.17.3 /home/xinxing06/DDS/mongo-c-driver-1.17.3/src/libmongoc /home/xinxing06/DDS/mongo-c-driver-1.17.3/cmake-build /home/xinxing06/DDS/mongo-c-driver-1.17.3/cmake-build/src/libmongoc /home/xinxing06/DDS/mongo-c-driver-1.17.3/cmake-build/src/libmongoc/CMakeFiles/mongoc-dump.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/libmongoc/CMakeFiles/mongoc-dump.dir/depend

