# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.14.5/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.14.5/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/daniel/Coder/Github/toolite/CMakeTool

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/daniel/Coder/Github/toolite/CMakeTool

# Include any dependencies generated for this target.
include CMakeFiles/power.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/power.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/power.dir/flags.make

CMakeFiles/power.dir/main.cpp.o: CMakeFiles/power.dir/flags.make
CMakeFiles/power.dir/main.cpp.o: main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/daniel/Coder/Github/toolite/CMakeTool/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/power.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/power.dir/main.cpp.o -c /Users/daniel/Coder/Github/toolite/CMakeTool/main.cpp

CMakeFiles/power.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/power.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/daniel/Coder/Github/toolite/CMakeTool/main.cpp > CMakeFiles/power.dir/main.cpp.i

CMakeFiles/power.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/power.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/daniel/Coder/Github/toolite/CMakeTool/main.cpp -o CMakeFiles/power.dir/main.cpp.s

# Object files for target power
power_OBJECTS = \
"CMakeFiles/power.dir/main.cpp.o"

# External object files for target power
power_EXTERNAL_OBJECTS =

power: CMakeFiles/power.dir/main.cpp.o
power: CMakeFiles/power.dir/build.make
power: math/libMathFunctions.a
power: CMakeFiles/power.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/daniel/Coder/Github/toolite/CMakeTool/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable power"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/power.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/power.dir/build: power

.PHONY : CMakeFiles/power.dir/build

CMakeFiles/power.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/power.dir/cmake_clean.cmake
.PHONY : CMakeFiles/power.dir/clean

CMakeFiles/power.dir/depend:
	cd /Users/daniel/Coder/Github/toolite/CMakeTool && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/daniel/Coder/Github/toolite/CMakeTool /Users/daniel/Coder/Github/toolite/CMakeTool /Users/daniel/Coder/Github/toolite/CMakeTool /Users/daniel/Coder/Github/toolite/CMakeTool /Users/daniel/Coder/Github/toolite/CMakeTool/CMakeFiles/power.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/power.dir/depend
