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
CMAKE_SOURCE_DIR = /Users/tenriku/Documents/GitHub/rpi-sound-effectorのコピー/audio_process

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/tenriku/Documents/GitHub/rpi-sound-effectorのコピー/audio_process/build

# Include any dependencies generated for this target.
include test/CMakeFiles/AudioProcess.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include test/CMakeFiles/AudioProcess.dir/compiler_depend.make

# Include the progress variables for this target.
include test/CMakeFiles/AudioProcess.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/AudioProcess.dir/flags.make

test/CMakeFiles/AudioProcess.dir/main.cc.o: test/CMakeFiles/AudioProcess.dir/flags.make
test/CMakeFiles/AudioProcess.dir/main.cc.o: /Users/tenriku/Documents/GitHub/rpi-sound-effectorのコピー/audio_process/test/main.cc
test/CMakeFiles/AudioProcess.dir/main.cc.o: test/CMakeFiles/AudioProcess.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/tenriku/Documents/GitHub/rpi-sound-effectorのコピー/audio_process/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/AudioProcess.dir/main.cc.o"
	cd /Users/tenriku/Documents/GitHub/rpi-sound-effectorのコピー/audio_process/build/test && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT test/CMakeFiles/AudioProcess.dir/main.cc.o -MF CMakeFiles/AudioProcess.dir/main.cc.o.d -o CMakeFiles/AudioProcess.dir/main.cc.o -c /Users/tenriku/Documents/GitHub/rpi-sound-effectorのコピー/audio_process/test/main.cc

test/CMakeFiles/AudioProcess.dir/main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/AudioProcess.dir/main.cc.i"
	cd /Users/tenriku/Documents/GitHub/rpi-sound-effectorのコピー/audio_process/build/test && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/tenriku/Documents/GitHub/rpi-sound-effectorのコピー/audio_process/test/main.cc > CMakeFiles/AudioProcess.dir/main.cc.i

test/CMakeFiles/AudioProcess.dir/main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/AudioProcess.dir/main.cc.s"
	cd /Users/tenriku/Documents/GitHub/rpi-sound-effectorのコピー/audio_process/build/test && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/tenriku/Documents/GitHub/rpi-sound-effectorのコピー/audio_process/test/main.cc -o CMakeFiles/AudioProcess.dir/main.cc.s

# Object files for target AudioProcess
AudioProcess_OBJECTS = \
"CMakeFiles/AudioProcess.dir/main.cc.o"

# External object files for target AudioProcess
AudioProcess_EXTERNAL_OBJECTS =

bin/AudioProcess: test/CMakeFiles/AudioProcess.dir/main.cc.o
bin/AudioProcess: test/CMakeFiles/AudioProcess.dir/build.make
bin/AudioProcess: lib/libconfig.dylib
bin/AudioProcess: /usr/local/lib/libportaudio.dylib
bin/AudioProcess: test/CMakeFiles/AudioProcess.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/tenriku/Documents/GitHub/rpi-sound-effectorのコピー/audio_process/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../bin/AudioProcess"
	cd /Users/tenriku/Documents/GitHub/rpi-sound-effectorのコピー/audio_process/build/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/AudioProcess.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/AudioProcess.dir/build: bin/AudioProcess
.PHONY : test/CMakeFiles/AudioProcess.dir/build

test/CMakeFiles/AudioProcess.dir/clean:
	cd /Users/tenriku/Documents/GitHub/rpi-sound-effectorのコピー/audio_process/build/test && $(CMAKE_COMMAND) -P CMakeFiles/AudioProcess.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/AudioProcess.dir/clean

test/CMakeFiles/AudioProcess.dir/depend:
	cd /Users/tenriku/Documents/GitHub/rpi-sound-effectorのコピー/audio_process/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/tenriku/Documents/GitHub/rpi-sound-effectorのコピー/audio_process /Users/tenriku/Documents/GitHub/rpi-sound-effectorのコピー/audio_process/test /Users/tenriku/Documents/GitHub/rpi-sound-effectorのコピー/audio_process/build /Users/tenriku/Documents/GitHub/rpi-sound-effectorのコピー/audio_process/build/test /Users/tenriku/Documents/GitHub/rpi-sound-effectorのコピー/audio_process/build/test/CMakeFiles/AudioProcess.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : test/CMakeFiles/AudioProcess.dir/depend

