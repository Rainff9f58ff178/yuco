# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_SOURCE_DIR = /home/rain/yuco

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/rain/yuco/build

# Include any dependencies generated for this target.
include uco/CMakeFiles/uco.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include uco/CMakeFiles/uco.dir/compiler_depend.make

# Include the progress variables for this target.
include uco/CMakeFiles/uco.dir/progress.make

# Include the compile flags for this target's objects.
include uco/CMakeFiles/uco.dir/flags.make

uco/CMakeFiles/uco.dir/Scheduler.cpp.o: uco/CMakeFiles/uco.dir/flags.make
uco/CMakeFiles/uco.dir/Scheduler.cpp.o: /home/rain/yuco/uco/Scheduler.cpp
uco/CMakeFiles/uco.dir/Scheduler.cpp.o: uco/CMakeFiles/uco.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/rain/yuco/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object uco/CMakeFiles/uco.dir/Scheduler.cpp.o"
	cd /home/rain/yuco/build/uco && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT uco/CMakeFiles/uco.dir/Scheduler.cpp.o -MF CMakeFiles/uco.dir/Scheduler.cpp.o.d -o CMakeFiles/uco.dir/Scheduler.cpp.o -c /home/rain/yuco/uco/Scheduler.cpp

uco/CMakeFiles/uco.dir/Scheduler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/uco.dir/Scheduler.cpp.i"
	cd /home/rain/yuco/build/uco && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/rain/yuco/uco/Scheduler.cpp > CMakeFiles/uco.dir/Scheduler.cpp.i

uco/CMakeFiles/uco.dir/Scheduler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/uco.dir/Scheduler.cpp.s"
	cd /home/rain/yuco/build/uco && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/rain/yuco/uco/Scheduler.cpp -o CMakeFiles/uco.dir/Scheduler.cpp.s

uco/CMakeFiles/uco.dir/AsyncScheduler.cpp.o: uco/CMakeFiles/uco.dir/flags.make
uco/CMakeFiles/uco.dir/AsyncScheduler.cpp.o: /home/rain/yuco/uco/AsyncScheduler.cpp
uco/CMakeFiles/uco.dir/AsyncScheduler.cpp.o: uco/CMakeFiles/uco.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/rain/yuco/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object uco/CMakeFiles/uco.dir/AsyncScheduler.cpp.o"
	cd /home/rain/yuco/build/uco && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT uco/CMakeFiles/uco.dir/AsyncScheduler.cpp.o -MF CMakeFiles/uco.dir/AsyncScheduler.cpp.o.d -o CMakeFiles/uco.dir/AsyncScheduler.cpp.o -c /home/rain/yuco/uco/AsyncScheduler.cpp

uco/CMakeFiles/uco.dir/AsyncScheduler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/uco.dir/AsyncScheduler.cpp.i"
	cd /home/rain/yuco/build/uco && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/rain/yuco/uco/AsyncScheduler.cpp > CMakeFiles/uco.dir/AsyncScheduler.cpp.i

uco/CMakeFiles/uco.dir/AsyncScheduler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/uco.dir/AsyncScheduler.cpp.s"
	cd /home/rain/yuco/build/uco && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/rain/yuco/uco/AsyncScheduler.cpp -o CMakeFiles/uco.dir/AsyncScheduler.cpp.s

# Object files for target uco
uco_OBJECTS = \
"CMakeFiles/uco.dir/Scheduler.cpp.o" \
"CMakeFiles/uco.dir/AsyncScheduler.cpp.o"

# External object files for target uco
uco_EXTERNAL_OBJECTS =

uco/libuco.a: uco/CMakeFiles/uco.dir/Scheduler.cpp.o
uco/libuco.a: uco/CMakeFiles/uco.dir/AsyncScheduler.cpp.o
uco/libuco.a: uco/CMakeFiles/uco.dir/build.make
uco/libuco.a: uco/CMakeFiles/uco.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/rain/yuco/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library libuco.a"
	cd /home/rain/yuco/build/uco && $(CMAKE_COMMAND) -P CMakeFiles/uco.dir/cmake_clean_target.cmake
	cd /home/rain/yuco/build/uco && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/uco.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
uco/CMakeFiles/uco.dir/build: uco/libuco.a
.PHONY : uco/CMakeFiles/uco.dir/build

uco/CMakeFiles/uco.dir/clean:
	cd /home/rain/yuco/build/uco && $(CMAKE_COMMAND) -P CMakeFiles/uco.dir/cmake_clean.cmake
.PHONY : uco/CMakeFiles/uco.dir/clean

uco/CMakeFiles/uco.dir/depend:
	cd /home/rain/yuco/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/rain/yuco /home/rain/yuco/uco /home/rain/yuco/build /home/rain/yuco/build/uco /home/rain/yuco/build/uco/CMakeFiles/uco.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : uco/CMakeFiles/uco.dir/depend

