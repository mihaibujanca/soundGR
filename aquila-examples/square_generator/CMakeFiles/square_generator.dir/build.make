# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.1

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.1.3/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.1.3/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/ian/Development/aquila/aquila-src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/ian/Development/aquila/aquila-build

# Include any dependencies generated for this target.
include examples/square_generator/CMakeFiles/square_generator.dir/depend.make

# Include the progress variables for this target.
include examples/square_generator/CMakeFiles/square_generator.dir/progress.make

# Include the compile flags for this target's objects.
include examples/square_generator/CMakeFiles/square_generator.dir/flags.make

examples/square_generator/CMakeFiles/square_generator.dir/square_generator.cpp.o: examples/square_generator/CMakeFiles/square_generator.dir/flags.make
examples/square_generator/CMakeFiles/square_generator.dir/square_generator.cpp.o: /Users/ian/Development/aquila/aquila-src/examples/square_generator/square_generator.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/ian/Development/aquila/aquila-build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object examples/square_generator/CMakeFiles/square_generator.dir/square_generator.cpp.o"
	cd /Users/ian/Development/aquila/aquila-build/examples/square_generator && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/square_generator.dir/square_generator.cpp.o -c /Users/ian/Development/aquila/aquila-src/examples/square_generator/square_generator.cpp

examples/square_generator/CMakeFiles/square_generator.dir/square_generator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/square_generator.dir/square_generator.cpp.i"
	cd /Users/ian/Development/aquila/aquila-build/examples/square_generator && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/ian/Development/aquila/aquila-src/examples/square_generator/square_generator.cpp > CMakeFiles/square_generator.dir/square_generator.cpp.i

examples/square_generator/CMakeFiles/square_generator.dir/square_generator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/square_generator.dir/square_generator.cpp.s"
	cd /Users/ian/Development/aquila/aquila-build/examples/square_generator && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/ian/Development/aquila/aquila-src/examples/square_generator/square_generator.cpp -o CMakeFiles/square_generator.dir/square_generator.cpp.s

examples/square_generator/CMakeFiles/square_generator.dir/square_generator.cpp.o.requires:
.PHONY : examples/square_generator/CMakeFiles/square_generator.dir/square_generator.cpp.o.requires

examples/square_generator/CMakeFiles/square_generator.dir/square_generator.cpp.o.provides: examples/square_generator/CMakeFiles/square_generator.dir/square_generator.cpp.o.requires
	$(MAKE) -f examples/square_generator/CMakeFiles/square_generator.dir/build.make examples/square_generator/CMakeFiles/square_generator.dir/square_generator.cpp.o.provides.build
.PHONY : examples/square_generator/CMakeFiles/square_generator.dir/square_generator.cpp.o.provides

examples/square_generator/CMakeFiles/square_generator.dir/square_generator.cpp.o.provides.build: examples/square_generator/CMakeFiles/square_generator.dir/square_generator.cpp.o

# Object files for target square_generator
square_generator_OBJECTS = \
"CMakeFiles/square_generator.dir/square_generator.cpp.o"

# External object files for target square_generator
square_generator_EXTERNAL_OBJECTS =

examples/square_generator/square_generator: examples/square_generator/CMakeFiles/square_generator.dir/square_generator.cpp.o
examples/square_generator/square_generator: examples/square_generator/CMakeFiles/square_generator.dir/build.make
examples/square_generator/square_generator: libAquila.a
examples/square_generator/square_generator: lib/libOoura_fft.a
examples/square_generator/square_generator: /usr/local/lib/libsfml-system.dylib
examples/square_generator/square_generator: /usr/local/lib/libsfml-audio.dylib
examples/square_generator/square_generator: examples/square_generator/CMakeFiles/square_generator.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable square_generator"
	cd /Users/ian/Development/aquila/aquila-build/examples/square_generator && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/square_generator.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/square_generator/CMakeFiles/square_generator.dir/build: examples/square_generator/square_generator
.PHONY : examples/square_generator/CMakeFiles/square_generator.dir/build

examples/square_generator/CMakeFiles/square_generator.dir/requires: examples/square_generator/CMakeFiles/square_generator.dir/square_generator.cpp.o.requires
.PHONY : examples/square_generator/CMakeFiles/square_generator.dir/requires

examples/square_generator/CMakeFiles/square_generator.dir/clean:
	cd /Users/ian/Development/aquila/aquila-build/examples/square_generator && $(CMAKE_COMMAND) -P CMakeFiles/square_generator.dir/cmake_clean.cmake
.PHONY : examples/square_generator/CMakeFiles/square_generator.dir/clean

examples/square_generator/CMakeFiles/square_generator.dir/depend:
	cd /Users/ian/Development/aquila/aquila-build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/ian/Development/aquila/aquila-src /Users/ian/Development/aquila/aquila-src/examples/square_generator /Users/ian/Development/aquila/aquila-build /Users/ian/Development/aquila/aquila-build/examples/square_generator /Users/ian/Development/aquila/aquila-build/examples/square_generator/CMakeFiles/square_generator.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/square_generator/CMakeFiles/square_generator.dir/depend

