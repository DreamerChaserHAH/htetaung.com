# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.31

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
CMAKE_COMMAND = /opt/homebrew/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/victormak/Projects/Personal/Projects/htetaung.com

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/victormak/Projects/Personal/Projects/htetaung.com/webbuild

# Include any dependencies generated for this target.
include CMakeFiles/text.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/text.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/text.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/text.dir/flags.make

CMakeFiles/text.dir/codegen:
.PHONY : CMakeFiles/text.dir/codegen

CMakeFiles/text.dir/src/text.cpp.o: CMakeFiles/text.dir/flags.make
CMakeFiles/text.dir/src/text.cpp.o: CMakeFiles/text.dir/includes_CXX.rsp
CMakeFiles/text.dir/src/text.cpp.o: /Users/victormak/Projects/Personal/Projects/htetaung.com/src/text.cpp
CMakeFiles/text.dir/src/text.cpp.o: CMakeFiles/text.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/victormak/Projects/Personal/Projects/htetaung.com/webbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/text.dir/src/text.cpp.o"
	/Users/victormak/emsdk/upstream/emscripten/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/text.dir/src/text.cpp.o -MF CMakeFiles/text.dir/src/text.cpp.o.d -o CMakeFiles/text.dir/src/text.cpp.o -c /Users/victormak/Projects/Personal/Projects/htetaung.com/src/text.cpp

CMakeFiles/text.dir/src/text.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/text.dir/src/text.cpp.i"
	/Users/victormak/emsdk/upstream/emscripten/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/victormak/Projects/Personal/Projects/htetaung.com/src/text.cpp > CMakeFiles/text.dir/src/text.cpp.i

CMakeFiles/text.dir/src/text.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/text.dir/src/text.cpp.s"
	/Users/victormak/emsdk/upstream/emscripten/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/victormak/Projects/Personal/Projects/htetaung.com/src/text.cpp -o CMakeFiles/text.dir/src/text.cpp.s

# Object files for target text
text_OBJECTS = \
"CMakeFiles/text.dir/src/text.cpp.o"

# External object files for target text
text_EXTERNAL_OBJECTS =

libtext.a: CMakeFiles/text.dir/src/text.cpp.o
libtext.a: CMakeFiles/text.dir/build.make
libtext.a: CMakeFiles/text.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/victormak/Projects/Personal/Projects/htetaung.com/webbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libtext.a"
	$(CMAKE_COMMAND) -P CMakeFiles/text.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/text.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/text.dir/build: libtext.a
.PHONY : CMakeFiles/text.dir/build

CMakeFiles/text.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/text.dir/cmake_clean.cmake
.PHONY : CMakeFiles/text.dir/clean

CMakeFiles/text.dir/depend:
	cd /Users/victormak/Projects/Personal/Projects/htetaung.com/webbuild && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/victormak/Projects/Personal/Projects/htetaung.com /Users/victormak/Projects/Personal/Projects/htetaung.com /Users/victormak/Projects/Personal/Projects/htetaung.com/webbuild /Users/victormak/Projects/Personal/Projects/htetaung.com/webbuild /Users/victormak/Projects/Personal/Projects/htetaung.com/webbuild/CMakeFiles/text.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/text.dir/depend
