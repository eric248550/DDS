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
include src/libbson/CMakeFiles/json-to-bson.dir/depend.make

# Include the progress variables for this target.
include src/libbson/CMakeFiles/json-to-bson.dir/progress.make

# Include the compile flags for this target's objects.
include src/libbson/CMakeFiles/json-to-bson.dir/flags.make

src/libbson/CMakeFiles/json-to-bson.dir/examples/json-to-bson.c.o: src/libbson/CMakeFiles/json-to-bson.dir/flags.make
src/libbson/CMakeFiles/json-to-bson.dir/examples/json-to-bson.c.o: ../src/libbson/examples/json-to-bson.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xinxing06/DDS/mongo-c-driver-1.17.3/cmake-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/libbson/CMakeFiles/json-to-bson.dir/examples/json-to-bson.c.o"
	cd /home/xinxing06/DDS/mongo-c-driver-1.17.3/cmake-build/src/libbson && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/json-to-bson.dir/examples/json-to-bson.c.o   -c /home/xinxing06/DDS/mongo-c-driver-1.17.3/src/libbson/examples/json-to-bson.c

src/libbson/CMakeFiles/json-to-bson.dir/examples/json-to-bson.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/json-to-bson.dir/examples/json-to-bson.c.i"
	cd /home/xinxing06/DDS/mongo-c-driver-1.17.3/cmake-build/src/libbson && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/xinxing06/DDS/mongo-c-driver-1.17.3/src/libbson/examples/json-to-bson.c > CMakeFiles/json-to-bson.dir/examples/json-to-bson.c.i

src/libbson/CMakeFiles/json-to-bson.dir/examples/json-to-bson.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/json-to-bson.dir/examples/json-to-bson.c.s"
	cd /home/xinxing06/DDS/mongo-c-driver-1.17.3/cmake-build/src/libbson && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/xinxing06/DDS/mongo-c-driver-1.17.3/src/libbson/examples/json-to-bson.c -o CMakeFiles/json-to-bson.dir/examples/json-to-bson.c.s

# Object files for target json-to-bson
json__to__bson_OBJECTS = \
"CMakeFiles/json-to-bson.dir/examples/json-to-bson.c.o"

# External object files for target json-to-bson
json__to__bson_EXTERNAL_OBJECTS =

src/libbson/json-to-bson: src/libbson/CMakeFiles/json-to-bson.dir/examples/json-to-bson.c.o
src/libbson/json-to-bson: src/libbson/CMakeFiles/json-to-bson.dir/build.make
src/libbson/json-to-bson: src/libbson/libbson-1.0.so.0.0.0
src/libbson/json-to-bson: src/libbson/CMakeFiles/json-to-bson.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/xinxing06/DDS/mongo-c-driver-1.17.3/cmake-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable json-to-bson"
	cd /home/xinxing06/DDS/mongo-c-driver-1.17.3/cmake-build/src/libbson && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/json-to-bson.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/libbson/CMakeFiles/json-to-bson.dir/build: src/libbson/json-to-bson

.PHONY : src/libbson/CMakeFiles/json-to-bson.dir/build

src/libbson/CMakeFiles/json-to-bson.dir/clean:
	cd /home/xinxing06/DDS/mongo-c-driver-1.17.3/cmake-build/src/libbson && $(CMAKE_COMMAND) -P CMakeFiles/json-to-bson.dir/cmake_clean.cmake
.PHONY : src/libbson/CMakeFiles/json-to-bson.dir/clean

src/libbson/CMakeFiles/json-to-bson.dir/depend:
	cd /home/xinxing06/DDS/mongo-c-driver-1.17.3/cmake-build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/xinxing06/DDS/mongo-c-driver-1.17.3 /home/xinxing06/DDS/mongo-c-driver-1.17.3/src/libbson /home/xinxing06/DDS/mongo-c-driver-1.17.3/cmake-build /home/xinxing06/DDS/mongo-c-driver-1.17.3/cmake-build/src/libbson /home/xinxing06/DDS/mongo-c-driver-1.17.3/cmake-build/src/libbson/CMakeFiles/json-to-bson.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/libbson/CMakeFiles/json-to-bson.dir/depend

