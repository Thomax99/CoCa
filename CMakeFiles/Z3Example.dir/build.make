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
CMAKE_SOURCE_DIR = /home/thomas/Documents/cocode

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/thomas/Documents/cocode

# Include any dependencies generated for this target.
include CMakeFiles/Z3Example.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Z3Example.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Z3Example.dir/flags.make

CMakeFiles/Z3Example.dir/examples/Z3Example.c.o: CMakeFiles/Z3Example.dir/flags.make
CMakeFiles/Z3Example.dir/examples/Z3Example.c.o: examples/Z3Example.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/thomas/Documents/cocode/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Z3Example.dir/examples/Z3Example.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Z3Example.dir/examples/Z3Example.c.o   -c /home/thomas/Documents/cocode/examples/Z3Example.c

CMakeFiles/Z3Example.dir/examples/Z3Example.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Z3Example.dir/examples/Z3Example.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/thomas/Documents/cocode/examples/Z3Example.c > CMakeFiles/Z3Example.dir/examples/Z3Example.c.i

CMakeFiles/Z3Example.dir/examples/Z3Example.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Z3Example.dir/examples/Z3Example.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/thomas/Documents/cocode/examples/Z3Example.c -o CMakeFiles/Z3Example.dir/examples/Z3Example.c.s

# Object files for target Z3Example
Z3Example_OBJECTS = \
"CMakeFiles/Z3Example.dir/examples/Z3Example.c.o"

# External object files for target Z3Example
Z3Example_EXTERNAL_OBJECTS =

Z3Example: CMakeFiles/Z3Example.dir/examples/Z3Example.c.o
Z3Example: CMakeFiles/Z3Example.dir/build.make
Z3Example: libmyZ3.a
Z3Example: CMakeFiles/Z3Example.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/thomas/Documents/cocode/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable Z3Example"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Z3Example.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Z3Example.dir/build: Z3Example

.PHONY : CMakeFiles/Z3Example.dir/build

CMakeFiles/Z3Example.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Z3Example.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Z3Example.dir/clean

CMakeFiles/Z3Example.dir/depend:
	cd /home/thomas/Documents/cocode && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/thomas/Documents/cocode /home/thomas/Documents/cocode /home/thomas/Documents/cocode /home/thomas/Documents/cocode /home/thomas/Documents/cocode/CMakeFiles/Z3Example.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Z3Example.dir/depend

