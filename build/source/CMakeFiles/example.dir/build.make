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

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/cmake-gui

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/arne/Repositories/programmiersprachen-raytracer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/arne/Repositories/programmiersprachen-raytracer/build

# Include any dependencies generated for this target.
include source/CMakeFiles/example.dir/depend.make

# Include the progress variables for this target.
include source/CMakeFiles/example.dir/progress.make

# Include the compile flags for this target's objects.
include source/CMakeFiles/example.dir/flags.make

source/CMakeFiles/example.dir/example.cpp.o: source/CMakeFiles/example.dir/flags.make
source/CMakeFiles/example.dir/example.cpp.o: ../source/example.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/arne/Repositories/programmiersprachen-raytracer/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object source/CMakeFiles/example.dir/example.cpp.o"
	cd /home/arne/Repositories/programmiersprachen-raytracer/build/source && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/example.dir/example.cpp.o -c /home/arne/Repositories/programmiersprachen-raytracer/source/example.cpp

source/CMakeFiles/example.dir/example.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/example.dir/example.cpp.i"
	cd /home/arne/Repositories/programmiersprachen-raytracer/build/source && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/arne/Repositories/programmiersprachen-raytracer/source/example.cpp > CMakeFiles/example.dir/example.cpp.i

source/CMakeFiles/example.dir/example.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/example.dir/example.cpp.s"
	cd /home/arne/Repositories/programmiersprachen-raytracer/build/source && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/arne/Repositories/programmiersprachen-raytracer/source/example.cpp -o CMakeFiles/example.dir/example.cpp.s

source/CMakeFiles/example.dir/example.cpp.o.requires:
.PHONY : source/CMakeFiles/example.dir/example.cpp.o.requires

source/CMakeFiles/example.dir/example.cpp.o.provides: source/CMakeFiles/example.dir/example.cpp.o.requires
	$(MAKE) -f source/CMakeFiles/example.dir/build.make source/CMakeFiles/example.dir/example.cpp.o.provides.build
.PHONY : source/CMakeFiles/example.dir/example.cpp.o.provides

source/CMakeFiles/example.dir/example.cpp.o.provides.build: source/CMakeFiles/example.dir/example.cpp.o

# Object files for target example
example_OBJECTS = \
"CMakeFiles/example.dir/example.cpp.o"

# External object files for target example
example_EXTERNAL_OBJECTS =

build/Release/example: source/CMakeFiles/example.dir/example.cpp.o
build/Release/example: source/CMakeFiles/example.dir/build.make
build/Release/example: framework/libframework.a
build/Release/example: external/glfw-3.0.3/src/libglfw3.a
build/Release/example: /usr/lib/x86_64-linux-gnu/libX11.so
build/Release/example: /usr/lib/x86_64-linux-gnu/libXrandr.so
build/Release/example: /usr/lib/x86_64-linux-gnu/libXi.so
build/Release/example: /usr/lib/x86_64-linux-gnu/libXxf86vm.so
build/Release/example: /usr/lib/x86_64-linux-gnu/librt.so
build/Release/example: /usr/lib/x86_64-linux-gnu/libm.so
build/Release/example: /usr/lib/x86_64-linux-gnu/libGL.so
build/Release/example: source/CMakeFiles/example.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../build/Release/example"
	cd /home/arne/Repositories/programmiersprachen-raytracer/build/source && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/example.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
source/CMakeFiles/example.dir/build: build/Release/example
.PHONY : source/CMakeFiles/example.dir/build

source/CMakeFiles/example.dir/requires: source/CMakeFiles/example.dir/example.cpp.o.requires
.PHONY : source/CMakeFiles/example.dir/requires

source/CMakeFiles/example.dir/clean:
	cd /home/arne/Repositories/programmiersprachen-raytracer/build/source && $(CMAKE_COMMAND) -P CMakeFiles/example.dir/cmake_clean.cmake
.PHONY : source/CMakeFiles/example.dir/clean

source/CMakeFiles/example.dir/depend:
	cd /home/arne/Repositories/programmiersprachen-raytracer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/arne/Repositories/programmiersprachen-raytracer /home/arne/Repositories/programmiersprachen-raytracer/source /home/arne/Repositories/programmiersprachen-raytracer/build /home/arne/Repositories/programmiersprachen-raytracer/build/source /home/arne/Repositories/programmiersprachen-raytracer/build/source/CMakeFiles/example.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : source/CMakeFiles/example.dir/depend

