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
CMAKE_SOURCE_DIR = /home/sanmu/c++/blog/myjson/1_tutorial

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sanmu/c++/blog/myjson/1_tutorial/build

# Include any dependencies generated for this target.
include CMakeFiles/leptjson.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/leptjson.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/leptjson.dir/flags.make

CMakeFiles/leptjson.dir/leptjson.cpp.o: CMakeFiles/leptjson.dir/flags.make
CMakeFiles/leptjson.dir/leptjson.cpp.o: ../leptjson.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sanmu/c++/blog/myjson/1_tutorial/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/leptjson.dir/leptjson.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/leptjson.dir/leptjson.cpp.o -c /home/sanmu/c++/blog/myjson/1_tutorial/leptjson.cpp

CMakeFiles/leptjson.dir/leptjson.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/leptjson.dir/leptjson.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sanmu/c++/blog/myjson/1_tutorial/leptjson.cpp > CMakeFiles/leptjson.dir/leptjson.cpp.i

CMakeFiles/leptjson.dir/leptjson.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/leptjson.dir/leptjson.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sanmu/c++/blog/myjson/1_tutorial/leptjson.cpp -o CMakeFiles/leptjson.dir/leptjson.cpp.s

# Object files for target leptjson
leptjson_OBJECTS = \
"CMakeFiles/leptjson.dir/leptjson.cpp.o"

# External object files for target leptjson
leptjson_EXTERNAL_OBJECTS =

libleptjson.a: CMakeFiles/leptjson.dir/leptjson.cpp.o
libleptjson.a: CMakeFiles/leptjson.dir/build.make
libleptjson.a: CMakeFiles/leptjson.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/sanmu/c++/blog/myjson/1_tutorial/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libleptjson.a"
	$(CMAKE_COMMAND) -P CMakeFiles/leptjson.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/leptjson.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/leptjson.dir/build: libleptjson.a

.PHONY : CMakeFiles/leptjson.dir/build

CMakeFiles/leptjson.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/leptjson.dir/cmake_clean.cmake
.PHONY : CMakeFiles/leptjson.dir/clean

CMakeFiles/leptjson.dir/depend:
	cd /home/sanmu/c++/blog/myjson/1_tutorial/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sanmu/c++/blog/myjson/1_tutorial /home/sanmu/c++/blog/myjson/1_tutorial /home/sanmu/c++/blog/myjson/1_tutorial/build /home/sanmu/c++/blog/myjson/1_tutorial/build /home/sanmu/c++/blog/myjson/1_tutorial/build/CMakeFiles/leptjson.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/leptjson.dir/depend

