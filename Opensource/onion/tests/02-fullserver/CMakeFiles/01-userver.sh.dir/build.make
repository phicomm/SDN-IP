# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/tetsuya/work/ON.Lab/BGP_SDN_without_onion/BGP-SDN/opensource/onion

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tetsuya/work/ON.Lab/BGP_SDN_without_onion/BGP-SDN/opensource/onion

# Utility rule file for 01-userver.sh.

# Include the progress variables for this target.
include tests/02-fullserver/CMakeFiles/01-userver.sh.dir/progress.make

tests/02-fullserver/CMakeFiles/01-userver.sh: examples/userver/userver

01-userver.sh: tests/02-fullserver/CMakeFiles/01-userver.sh
01-userver.sh: tests/02-fullserver/CMakeFiles/01-userver.sh.dir/build.make
.PHONY : 01-userver.sh

# Rule to build all files generated by this target.
tests/02-fullserver/CMakeFiles/01-userver.sh.dir/build: 01-userver.sh
.PHONY : tests/02-fullserver/CMakeFiles/01-userver.sh.dir/build

tests/02-fullserver/CMakeFiles/01-userver.sh.dir/clean:
	cd /home/tetsuya/work/ON.Lab/BGP_SDN_without_onion/BGP-SDN/opensource/onion/tests/02-fullserver && $(CMAKE_COMMAND) -P CMakeFiles/01-userver.sh.dir/cmake_clean.cmake
.PHONY : tests/02-fullserver/CMakeFiles/01-userver.sh.dir/clean

tests/02-fullserver/CMakeFiles/01-userver.sh.dir/depend:
	cd /home/tetsuya/work/ON.Lab/BGP_SDN_without_onion/BGP-SDN/opensource/onion && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tetsuya/work/ON.Lab/BGP_SDN_without_onion/BGP-SDN/opensource/onion /home/tetsuya/work/ON.Lab/BGP_SDN_without_onion/BGP-SDN/opensource/onion/tests/02-fullserver /home/tetsuya/work/ON.Lab/BGP_SDN_without_onion/BGP-SDN/opensource/onion /home/tetsuya/work/ON.Lab/BGP_SDN_without_onion/BGP-SDN/opensource/onion/tests/02-fullserver /home/tetsuya/work/ON.Lab/BGP_SDN_without_onion/BGP-SDN/opensource/onion/tests/02-fullserver/CMakeFiles/01-userver.sh.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/02-fullserver/CMakeFiles/01-userver.sh.dir/depend

