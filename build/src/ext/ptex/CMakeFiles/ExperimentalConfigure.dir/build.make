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

# Utility rule file for ExperimentalConfigure.

# Include the progress variables for this target.
include src/ext/ptex/CMakeFiles/ExperimentalConfigure.dir/progress.make

src/ext/ptex/CMakeFiles/ExperimentalConfigure:
	cd /mnt/c/Users/mikec/Documents/GitHub/pbrt-v3/build/src/ext/ptex && /usr/bin/ctest -D ExperimentalConfigure

ExperimentalConfigure: src/ext/ptex/CMakeFiles/ExperimentalConfigure
ExperimentalConfigure: src/ext/ptex/CMakeFiles/ExperimentalConfigure.dir/build.make

.PHONY : ExperimentalConfigure

# Rule to build all files generated by this target.
src/ext/ptex/CMakeFiles/ExperimentalConfigure.dir/build: ExperimentalConfigure

.PHONY : src/ext/ptex/CMakeFiles/ExperimentalConfigure.dir/build

src/ext/ptex/CMakeFiles/ExperimentalConfigure.dir/clean:
	cd /mnt/c/Users/mikec/Documents/GitHub/pbrt-v3/build/src/ext/ptex && $(CMAKE_COMMAND) -P CMakeFiles/ExperimentalConfigure.dir/cmake_clean.cmake
.PHONY : src/ext/ptex/CMakeFiles/ExperimentalConfigure.dir/clean

src/ext/ptex/CMakeFiles/ExperimentalConfigure.dir/depend:
	cd /mnt/c/Users/mikec/Documents/GitHub/pbrt-v3/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/mikec/Documents/GitHub/pbrt-v3 /mnt/c/Users/mikec/Documents/GitHub/pbrt-v3/src/ext/ptex /mnt/c/Users/mikec/Documents/GitHub/pbrt-v3/build /mnt/c/Users/mikec/Documents/GitHub/pbrt-v3/build/src/ext/ptex /mnt/c/Users/mikec/Documents/GitHub/pbrt-v3/build/src/ext/ptex/CMakeFiles/ExperimentalConfigure.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/ext/ptex/CMakeFiles/ExperimentalConfigure.dir/depend

