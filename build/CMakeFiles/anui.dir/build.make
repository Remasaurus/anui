# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/Daniel/Dev/Anui

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/Daniel/Dev/Anui/build

# Include any dependencies generated for this target.
include CMakeFiles/anui.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/anui.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/anui.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/anui.dir/flags.make

CMakeFiles/anui.dir/src/x11/window.cpp.o: CMakeFiles/anui.dir/flags.make
CMakeFiles/anui.dir/src/x11/window.cpp.o: /home/Daniel/Dev/Anui/src/x11/window.cpp
CMakeFiles/anui.dir/src/x11/window.cpp.o: CMakeFiles/anui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/Daniel/Dev/Anui/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/anui.dir/src/x11/window.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/anui.dir/src/x11/window.cpp.o -MF CMakeFiles/anui.dir/src/x11/window.cpp.o.d -o CMakeFiles/anui.dir/src/x11/window.cpp.o -c /home/Daniel/Dev/Anui/src/x11/window.cpp

CMakeFiles/anui.dir/src/x11/window.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/anui.dir/src/x11/window.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/Daniel/Dev/Anui/src/x11/window.cpp > CMakeFiles/anui.dir/src/x11/window.cpp.i

CMakeFiles/anui.dir/src/x11/window.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/anui.dir/src/x11/window.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/Daniel/Dev/Anui/src/x11/window.cpp -o CMakeFiles/anui.dir/src/x11/window.cpp.s

# Object files for target anui
anui_OBJECTS = \
"CMakeFiles/anui.dir/src/x11/window.cpp.o"

# External object files for target anui
anui_EXTERNAL_OBJECTS =

libanui.a: CMakeFiles/anui.dir/src/x11/window.cpp.o
libanui.a: CMakeFiles/anui.dir/build.make
libanui.a: CMakeFiles/anui.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/Daniel/Dev/Anui/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libanui.a"
	$(CMAKE_COMMAND) -P CMakeFiles/anui.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/anui.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/anui.dir/build: libanui.a
.PHONY : CMakeFiles/anui.dir/build

CMakeFiles/anui.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/anui.dir/cmake_clean.cmake
.PHONY : CMakeFiles/anui.dir/clean

CMakeFiles/anui.dir/depend:
	cd /home/Daniel/Dev/Anui/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/Daniel/Dev/Anui /home/Daniel/Dev/Anui /home/Daniel/Dev/Anui/build /home/Daniel/Dev/Anui/build /home/Daniel/Dev/Anui/build/CMakeFiles/anui.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/anui.dir/depend

