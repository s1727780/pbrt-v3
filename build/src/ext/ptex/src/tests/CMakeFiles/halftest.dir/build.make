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
include src/ext/ptex/src/tests/CMakeFiles/halftest.dir/depend.make

# Include the progress variables for this target.
include src/ext/ptex/src/tests/CMakeFiles/halftest.dir/progress.make

# Include the compile flags for this target's objects.
include src/ext/ptex/src/tests/CMakeFiles/halftest.dir/flags.make

src/ext/ptex/src/tests/CMakeFiles/halftest.dir/halftest.cpp.o: src/ext/ptex/src/tests/CMakeFiles/halftest.dir/flags.make
src/ext/ptex/src/tests/CMakeFiles/halftest.dir/halftest.cpp.o: ../src/ext/ptex/src/tests/halftest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/mikec/Documents/GitHub/pbrt-v3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/ext/ptex/src/tests/CMakeFiles/halftest.dir/halftest.cpp.o"
	cd /mnt/c/Users/mikec/Documents/GitHub/pbrt-v3/build/src/ext/ptex/src/tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/halftest.dir/halftest.cpp.o -c /mnt/c/Users/mikec/Documents/GitHub/pbrt-v3/src/ext/ptex/src/tests/halftest.cpp

src/ext/ptex/src/tests/CMakeFiles/halftest.dir/halftest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/halftest.dir/halftest.cpp.i"
	cd /mnt/c/Users/mikec/Documents/GitHub/pbrt-v3/build/src/ext/ptex/src/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/mikec/Documents/GitHub/pbrt-v3/src/ext/ptex/src/tests/halftest.cpp > CMakeFiles/halftest.dir/halftest.cpp.i

src/ext/ptex/src/tests/CMakeFiles/halftest.dir/halftest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/halftest.dir/halftest.cpp.s"
	cd /mnt/c/Users/mikec/Documents/GitHub/pbrt-v3/build/src/ext/ptex/src/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/mikec/Documents/GitHub/pbrt-v3/src/ext/ptex/src/tests/halftest.cpp -o CMakeFiles/halftest.dir/halftest.cpp.s

# Object files for target halftest
halftest_OBJECTS = \
"CMakeFiles/halftest.dir/halftest.cpp.o"

# External object files for target halftest
halftest_EXTERNAL_OBJECTS =

src/ext/ptex/src/tests/halftest: src/ext/ptex/src/tests/CMakeFiles/halftest.dir/halftest.cpp.o
src/ext/ptex/src/tests/halftest: src/ext/ptex/src/tests/CMakeFiles/halftest.dir/build.make
src/ext/ptex/src/tests/halftest: src/ext/ptex/src/ptex/libPtex.a
src/ext/ptex/src/tests/halftest: /usr/lib/x86_64-linux-gnu/libz.so
src/ext/ptex/src/tests/halftest: src/ext/ptex/src/tests/CMakeFiles/halftest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/mikec/Documents/GitHub/pbrt-v3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable halftest"
	cd /mnt/c/Users/mikec/Documents/GitHub/pbrt-v3/build/src/ext/ptex/src/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/halftest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/ext/ptex/src/tests/CMakeFiles/halftest.dir/build: src/ext/ptex/src/tests/halftest

.PHONY : src/ext/ptex/src/tests/CMakeFiles/halftest.dir/build

src/ext/ptex/src/tests/CMakeFiles/halftest.dir/clean:
	cd /mnt/c/Users/mikec/Documents/GitHub/pbrt-v3/build/src/ext/ptex/src/tests && $(CMAKE_COMMAND) -P CMakeFiles/halftest.dir/cmake_clean.cmake
.PHONY : src/ext/ptex/src/tests/CMakeFiles/halftest.dir/clean

src/ext/ptex/src/tests/CMakeFiles/halftest.dir/depend:
	cd /mnt/c/Users/mikec/Documents/GitHub/pbrt-v3/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/mikec/Documents/GitHub/pbrt-v3 /mnt/c/Users/mikec/Documents/GitHub/pbrt-v3/src/ext/ptex/src/tests /mnt/c/Users/mikec/Documents/GitHub/pbrt-v3/build /mnt/c/Users/mikec/Documents/GitHub/pbrt-v3/build/src/ext/ptex/src/tests /mnt/c/Users/mikec/Documents/GitHub/pbrt-v3/build/src/ext/ptex/src/tests/CMakeFiles/halftest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/ext/ptex/src/tests/CMakeFiles/halftest.dir/depend

