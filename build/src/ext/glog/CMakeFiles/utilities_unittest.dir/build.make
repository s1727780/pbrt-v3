# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /mnt/c/Users/mikec/Documents/GitHub/pbrt-v3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/mikec/Documents/GitHub/pbrt-v3/build

# Include any dependencies generated for this target.
include src/ext/glog/CMakeFiles/utilities_unittest.dir/depend.make

# Include the progress variables for this target.
include src/ext/glog/CMakeFiles/utilities_unittest.dir/progress.make

# Include the compile flags for this target's objects.
include src/ext/glog/CMakeFiles/utilities_unittest.dir/flags.make

src/ext/glog/CMakeFiles/utilities_unittest.dir/src/utilities_unittest.cc.o: src/ext/glog/CMakeFiles/utilities_unittest.dir/flags.make
src/ext/glog/CMakeFiles/utilities_unittest.dir/src/utilities_unittest.cc.o: ../src/ext/glog/src/utilities_unittest.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/mikec/Documents/GitHub/pbrt-v3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/ext/glog/CMakeFiles/utilities_unittest.dir/src/utilities_unittest.cc.o"
	cd /mnt/c/Users/mikec/Documents/GitHub/pbrt-v3/build/src/ext/glog && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/utilities_unittest.dir/src/utilities_unittest.cc.o -c /mnt/c/Users/mikec/Documents/GitHub/pbrt-v3/src/ext/glog/src/utilities_unittest.cc

src/ext/glog/CMakeFiles/utilities_unittest.dir/src/utilities_unittest.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/utilities_unittest.dir/src/utilities_unittest.cc.i"
	cd /mnt/c/Users/mikec/Documents/GitHub/pbrt-v3/build/src/ext/glog && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/mikec/Documents/GitHub/pbrt-v3/src/ext/glog/src/utilities_unittest.cc > CMakeFiles/utilities_unittest.dir/src/utilities_unittest.cc.i

src/ext/glog/CMakeFiles/utilities_unittest.dir/src/utilities_unittest.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/utilities_unittest.dir/src/utilities_unittest.cc.s"
	cd /mnt/c/Users/mikec/Documents/GitHub/pbrt-v3/build/src/ext/glog && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/mikec/Documents/GitHub/pbrt-v3/src/ext/glog/src/utilities_unittest.cc -o CMakeFiles/utilities_unittest.dir/src/utilities_unittest.cc.s

# Object files for target utilities_unittest
utilities_unittest_OBJECTS = \
"CMakeFiles/utilities_unittest.dir/src/utilities_unittest.cc.o"

# External object files for target utilities_unittest
utilities_unittest_EXTERNAL_OBJECTS =

src/ext/glog/utilities_unittest: src/ext/glog/CMakeFiles/utilities_unittest.dir/src/utilities_unittest.cc.o
src/ext/glog/utilities_unittest: src/ext/glog/CMakeFiles/utilities_unittest.dir/build.make
src/ext/glog/utilities_unittest: src/ext/glog/libglog.a
src/ext/glog/utilities_unittest: src/ext/glog/CMakeFiles/utilities_unittest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/mikec/Documents/GitHub/pbrt-v3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable utilities_unittest"
	cd /mnt/c/Users/mikec/Documents/GitHub/pbrt-v3/build/src/ext/glog && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/utilities_unittest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/ext/glog/CMakeFiles/utilities_unittest.dir/build: src/ext/glog/utilities_unittest

.PHONY : src/ext/glog/CMakeFiles/utilities_unittest.dir/build

src/ext/glog/CMakeFiles/utilities_unittest.dir/clean:
	cd /mnt/c/Users/mikec/Documents/GitHub/pbrt-v3/build/src/ext/glog && $(CMAKE_COMMAND) -P CMakeFiles/utilities_unittest.dir/cmake_clean.cmake
.PHONY : src/ext/glog/CMakeFiles/utilities_unittest.dir/clean

src/ext/glog/CMakeFiles/utilities_unittest.dir/depend:
	cd /mnt/c/Users/mikec/Documents/GitHub/pbrt-v3/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/mikec/Documents/GitHub/pbrt-v3 /mnt/c/Users/mikec/Documents/GitHub/pbrt-v3/src/ext/glog /mnt/c/Users/mikec/Documents/GitHub/pbrt-v3/build /mnt/c/Users/mikec/Documents/GitHub/pbrt-v3/build/src/ext/glog /mnt/c/Users/mikec/Documents/GitHub/pbrt-v3/build/src/ext/glog/CMakeFiles/utilities_unittest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/ext/glog/CMakeFiles/utilities_unittest.dir/depend

