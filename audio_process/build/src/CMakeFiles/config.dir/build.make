# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.30.2/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.30.2/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/tenriku/Documents/GitHub/rpi-sound-effector/audio_process

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/tenriku/Documents/GitHub/rpi-sound-effector/audio_process/build

# Include any dependencies generated for this target.
include src/CMakeFiles/config.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/CMakeFiles/config.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/config.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/config.dir/flags.make

src/CMakeFiles/config.dir/config.cc.o: src/CMakeFiles/config.dir/flags.make
src/CMakeFiles/config.dir/config.cc.o: /Users/tenriku/Documents/GitHub/rpi-sound-effector/audio_process/src/config.cc
src/CMakeFiles/config.dir/config.cc.o: src/CMakeFiles/config.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/tenriku/Documents/GitHub/rpi-sound-effector/audio_process/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/config.dir/config.cc.o"
	cd /Users/tenriku/Documents/GitHub/rpi-sound-effector/audio_process/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/config.dir/config.cc.o -MF CMakeFiles/config.dir/config.cc.o.d -o CMakeFiles/config.dir/config.cc.o -c /Users/tenriku/Documents/GitHub/rpi-sound-effector/audio_process/src/config.cc

src/CMakeFiles/config.dir/config.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/config.dir/config.cc.i"
	cd /Users/tenriku/Documents/GitHub/rpi-sound-effector/audio_process/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/tenriku/Documents/GitHub/rpi-sound-effector/audio_process/src/config.cc > CMakeFiles/config.dir/config.cc.i

src/CMakeFiles/config.dir/config.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/config.dir/config.cc.s"
	cd /Users/tenriku/Documents/GitHub/rpi-sound-effector/audio_process/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/tenriku/Documents/GitHub/rpi-sound-effector/audio_process/src/config.cc -o CMakeFiles/config.dir/config.cc.s

src/CMakeFiles/config.dir/basic.cc.o: src/CMakeFiles/config.dir/flags.make
src/CMakeFiles/config.dir/basic.cc.o: /Users/tenriku/Documents/GitHub/rpi-sound-effector/audio_process/src/basic.cc
src/CMakeFiles/config.dir/basic.cc.o: src/CMakeFiles/config.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/tenriku/Documents/GitHub/rpi-sound-effector/audio_process/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/config.dir/basic.cc.o"
	cd /Users/tenriku/Documents/GitHub/rpi-sound-effector/audio_process/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/config.dir/basic.cc.o -MF CMakeFiles/config.dir/basic.cc.o.d -o CMakeFiles/config.dir/basic.cc.o -c /Users/tenriku/Documents/GitHub/rpi-sound-effector/audio_process/src/basic.cc

src/CMakeFiles/config.dir/basic.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/config.dir/basic.cc.i"
	cd /Users/tenriku/Documents/GitHub/rpi-sound-effector/audio_process/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/tenriku/Documents/GitHub/rpi-sound-effector/audio_process/src/basic.cc > CMakeFiles/config.dir/basic.cc.i

src/CMakeFiles/config.dir/basic.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/config.dir/basic.cc.s"
	cd /Users/tenriku/Documents/GitHub/rpi-sound-effector/audio_process/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/tenriku/Documents/GitHub/rpi-sound-effector/audio_process/src/basic.cc -o CMakeFiles/config.dir/basic.cc.s

# Object files for target config
config_OBJECTS = \
"CMakeFiles/config.dir/config.cc.o" \
"CMakeFiles/config.dir/basic.cc.o"

# External object files for target config
config_EXTERNAL_OBJECTS =

lib/libconfig.dylib: src/CMakeFiles/config.dir/config.cc.o
lib/libconfig.dylib: src/CMakeFiles/config.dir/basic.cc.o
lib/libconfig.dylib: src/CMakeFiles/config.dir/build.make
lib/libconfig.dylib: src/CMakeFiles/config.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/tenriku/Documents/GitHub/rpi-sound-effector/audio_process/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX shared library ../lib/libconfig.dylib"
	cd /Users/tenriku/Documents/GitHub/rpi-sound-effector/audio_process/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/config.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/config.dir/build: lib/libconfig.dylib
.PHONY : src/CMakeFiles/config.dir/build

src/CMakeFiles/config.dir/clean:
	cd /Users/tenriku/Documents/GitHub/rpi-sound-effector/audio_process/build/src && $(CMAKE_COMMAND) -P CMakeFiles/config.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/config.dir/clean

src/CMakeFiles/config.dir/depend:
	cd /Users/tenriku/Documents/GitHub/rpi-sound-effector/audio_process/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/tenriku/Documents/GitHub/rpi-sound-effector/audio_process /Users/tenriku/Documents/GitHub/rpi-sound-effector/audio_process/src /Users/tenriku/Documents/GitHub/rpi-sound-effector/audio_process/build /Users/tenriku/Documents/GitHub/rpi-sound-effector/audio_process/build/src /Users/tenriku/Documents/GitHub/rpi-sound-effector/audio_process/build/src/CMakeFiles/config.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : src/CMakeFiles/config.dir/depend

