# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_SOURCE_DIR = /home/thomas/Documents/Cours/code

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/thomas/Documents/Cours/code

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/thomas/Documents/Cours/code/CMakeFiles /home/thomas/Documents/Cours/code/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/thomas/Documents/Cours/code/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named graphParser

# Build rule for target.
graphParser: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 graphParser
.PHONY : graphParser

# fast build rule for target.
graphParser/fast:
	$(MAKE) -f CMakeFiles/graphParser.dir/build.make CMakeFiles/graphParser.dir/build
.PHONY : graphParser/fast

#=============================================================================
# Target rules for targets named graphProblemSolver

# Build rule for target.
graphProblemSolver: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 graphProblemSolver
.PHONY : graphProblemSolver

# fast build rule for target.
graphProblemSolver/fast:
	$(MAKE) -f CMakeFiles/graphProblemSolver.dir/build.make CMakeFiles/graphProblemSolver.dir/build
.PHONY : graphProblemSolver/fast

#=============================================================================
# Target rules for targets named biCon

# Build rule for target.
biCon: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 biCon
.PHONY : biCon

# fast build rule for target.
biCon/fast:
	$(MAKE) -f CMakeFiles/biCon.dir/build.make CMakeFiles/biCon.dir/build
.PHONY : biCon/fast

#=============================================================================
# Target rules for targets named Z3Example

# Build rule for target.
Z3Example: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 Z3Example
.PHONY : Z3Example

# fast build rule for target.
Z3Example/fast:
	$(MAKE) -f CMakeFiles/Z3Example.dir/build.make CMakeFiles/Z3Example.dir/build
.PHONY : Z3Example/fast

#=============================================================================
# Target rules for targets named parser

# Build rule for target.
parser: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 parser
.PHONY : parser

# fast build rule for target.
parser/fast:
	$(MAKE) -f CMakeFiles/parser.dir/build.make CMakeFiles/parser.dir/build
.PHONY : parser/fast

#=============================================================================
# Target rules for targets named myZ3

# Build rule for target.
myZ3: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 myZ3
.PHONY : myZ3

# fast build rule for target.
myZ3/fast:
	$(MAKE) -f CMakeFiles/myZ3.dir/build.make CMakeFiles/myZ3.dir/build
.PHONY : myZ3/fast

#=============================================================================
# Target rules for targets named myGraph

# Build rule for target.
myGraph: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 myGraph
.PHONY : myGraph

# fast build rule for target.
myGraph/fast:
	$(MAKE) -f CMakeFiles/myGraph.dir/build.make CMakeFiles/myGraph.dir/build
.PHONY : myGraph/fast

Lexer.o: Lexer.c.o

.PHONY : Lexer.o

# target to build an object file
Lexer.c.o:
	$(MAKE) -f CMakeFiles/parser.dir/build.make CMakeFiles/parser.dir/Lexer.c.o
.PHONY : Lexer.c.o

Lexer.i: Lexer.c.i

.PHONY : Lexer.i

# target to preprocess a source file
Lexer.c.i:
	$(MAKE) -f CMakeFiles/parser.dir/build.make CMakeFiles/parser.dir/Lexer.c.i
.PHONY : Lexer.c.i

Lexer.s: Lexer.c.s

.PHONY : Lexer.s

# target to generate assembly for a file
Lexer.c.s:
	$(MAKE) -f CMakeFiles/parser.dir/build.make CMakeFiles/parser.dir/Lexer.c.s
.PHONY : Lexer.c.s

Parser.o: Parser.c.o

.PHONY : Parser.o

# target to build an object file
Parser.c.o:
	$(MAKE) -f CMakeFiles/parser.dir/build.make CMakeFiles/parser.dir/Parser.c.o
.PHONY : Parser.c.o

Parser.i: Parser.c.i

.PHONY : Parser.i

# target to preprocess a source file
Parser.c.i:
	$(MAKE) -f CMakeFiles/parser.dir/build.make CMakeFiles/parser.dir/Parser.c.i
.PHONY : Parser.c.i

Parser.s: Parser.c.s

.PHONY : Parser.s

# target to generate assembly for a file
Parser.c.s:
	$(MAKE) -f CMakeFiles/parser.dir/build.make CMakeFiles/parser.dir/Parser.c.s
.PHONY : Parser.c.s

examples/Z3Example.o: examples/Z3Example.c.o

.PHONY : examples/Z3Example.o

# target to build an object file
examples/Z3Example.c.o:
	$(MAKE) -f CMakeFiles/Z3Example.dir/build.make CMakeFiles/Z3Example.dir/examples/Z3Example.c.o
.PHONY : examples/Z3Example.c.o

examples/Z3Example.i: examples/Z3Example.c.i

.PHONY : examples/Z3Example.i

# target to preprocess a source file
examples/Z3Example.c.i:
	$(MAKE) -f CMakeFiles/Z3Example.dir/build.make CMakeFiles/Z3Example.dir/examples/Z3Example.c.i
.PHONY : examples/Z3Example.c.i

examples/Z3Example.s: examples/Z3Example.c.s

.PHONY : examples/Z3Example.s

# target to generate assembly for a file
examples/Z3Example.c.s:
	$(MAKE) -f CMakeFiles/Z3Example.dir/build.make CMakeFiles/Z3Example.dir/examples/Z3Example.c.s
.PHONY : examples/Z3Example.c.s

examples/graphUsage.o: examples/graphUsage.c.o

.PHONY : examples/graphUsage.o

# target to build an object file
examples/graphUsage.c.o:
	$(MAKE) -f CMakeFiles/graphParser.dir/build.make CMakeFiles/graphParser.dir/examples/graphUsage.c.o
.PHONY : examples/graphUsage.c.o

examples/graphUsage.i: examples/graphUsage.c.i

.PHONY : examples/graphUsage.i

# target to preprocess a source file
examples/graphUsage.c.i:
	$(MAKE) -f CMakeFiles/graphParser.dir/build.make CMakeFiles/graphParser.dir/examples/graphUsage.c.i
.PHONY : examples/graphUsage.c.i

examples/graphUsage.s: examples/graphUsage.c.s

.PHONY : examples/graphUsage.s

# target to generate assembly for a file
examples/graphUsage.c.s:
	$(MAKE) -f CMakeFiles/graphParser.dir/build.make CMakeFiles/graphParser.dir/examples/graphUsage.c.s
.PHONY : examples/graphUsage.c.s

src/EdgeConProblem/EdgeConGraph.o: src/EdgeConProblem/EdgeConGraph.c.o

.PHONY : src/EdgeConProblem/EdgeConGraph.o

# target to build an object file
src/EdgeConProblem/EdgeConGraph.c.o:
	$(MAKE) -f CMakeFiles/biCon.dir/build.make CMakeFiles/biCon.dir/src/EdgeConProblem/EdgeConGraph.c.o
.PHONY : src/EdgeConProblem/EdgeConGraph.c.o

src/EdgeConProblem/EdgeConGraph.i: src/EdgeConProblem/EdgeConGraph.c.i

.PHONY : src/EdgeConProblem/EdgeConGraph.i

# target to preprocess a source file
src/EdgeConProblem/EdgeConGraph.c.i:
	$(MAKE) -f CMakeFiles/biCon.dir/build.make CMakeFiles/biCon.dir/src/EdgeConProblem/EdgeConGraph.c.i
.PHONY : src/EdgeConProblem/EdgeConGraph.c.i

src/EdgeConProblem/EdgeConGraph.s: src/EdgeConProblem/EdgeConGraph.c.s

.PHONY : src/EdgeConProblem/EdgeConGraph.s

# target to generate assembly for a file
src/EdgeConProblem/EdgeConGraph.c.s:
	$(MAKE) -f CMakeFiles/biCon.dir/build.make CMakeFiles/biCon.dir/src/EdgeConProblem/EdgeConGraph.c.s
.PHONY : src/EdgeConProblem/EdgeConGraph.c.s

src/EdgeConProblem/EdgeConReduction.o: src/EdgeConProblem/EdgeConReduction.c.o

.PHONY : src/EdgeConProblem/EdgeConReduction.o

# target to build an object file
src/EdgeConProblem/EdgeConReduction.c.o:
	$(MAKE) -f CMakeFiles/biCon.dir/build.make CMakeFiles/biCon.dir/src/EdgeConProblem/EdgeConReduction.c.o
.PHONY : src/EdgeConProblem/EdgeConReduction.c.o

src/EdgeConProblem/EdgeConReduction.i: src/EdgeConProblem/EdgeConReduction.c.i

.PHONY : src/EdgeConProblem/EdgeConReduction.i

# target to preprocess a source file
src/EdgeConProblem/EdgeConReduction.c.i:
	$(MAKE) -f CMakeFiles/biCon.dir/build.make CMakeFiles/biCon.dir/src/EdgeConProblem/EdgeConReduction.c.i
.PHONY : src/EdgeConProblem/EdgeConReduction.c.i

src/EdgeConProblem/EdgeConReduction.s: src/EdgeConProblem/EdgeConReduction.c.s

.PHONY : src/EdgeConProblem/EdgeConReduction.s

# target to generate assembly for a file
src/EdgeConProblem/EdgeConReduction.c.s:
	$(MAKE) -f CMakeFiles/biCon.dir/build.make CMakeFiles/biCon.dir/src/EdgeConProblem/EdgeConReduction.c.s
.PHONY : src/EdgeConProblem/EdgeConReduction.c.s

src/EdgeConProblem/EdgeConResolution.o: src/EdgeConProblem/EdgeConResolution.c.o

.PHONY : src/EdgeConProblem/EdgeConResolution.o

# target to build an object file
src/EdgeConProblem/EdgeConResolution.c.o:
	$(MAKE) -f CMakeFiles/biCon.dir/build.make CMakeFiles/biCon.dir/src/EdgeConProblem/EdgeConResolution.c.o
.PHONY : src/EdgeConProblem/EdgeConResolution.c.o

src/EdgeConProblem/EdgeConResolution.i: src/EdgeConProblem/EdgeConResolution.c.i

.PHONY : src/EdgeConProblem/EdgeConResolution.i

# target to preprocess a source file
src/EdgeConProblem/EdgeConResolution.c.i:
	$(MAKE) -f CMakeFiles/biCon.dir/build.make CMakeFiles/biCon.dir/src/EdgeConProblem/EdgeConResolution.c.i
.PHONY : src/EdgeConProblem/EdgeConResolution.c.i

src/EdgeConProblem/EdgeConResolution.s: src/EdgeConProblem/EdgeConResolution.c.s

.PHONY : src/EdgeConProblem/EdgeConResolution.s

# target to generate assembly for a file
src/EdgeConProblem/EdgeConResolution.c.s:
	$(MAKE) -f CMakeFiles/biCon.dir/build.make CMakeFiles/biCon.dir/src/EdgeConProblem/EdgeConResolution.c.s
.PHONY : src/EdgeConProblem/EdgeConResolution.c.s

src/main/Graph.o: src/main/Graph.c.o

.PHONY : src/main/Graph.o

# target to build an object file
src/main/Graph.c.o:
	$(MAKE) -f CMakeFiles/myGraph.dir/build.make CMakeFiles/myGraph.dir/src/main/Graph.c.o
.PHONY : src/main/Graph.c.o

src/main/Graph.i: src/main/Graph.c.i

.PHONY : src/main/Graph.i

# target to preprocess a source file
src/main/Graph.c.i:
	$(MAKE) -f CMakeFiles/myGraph.dir/build.make CMakeFiles/myGraph.dir/src/main/Graph.c.i
.PHONY : src/main/Graph.c.i

src/main/Graph.s: src/main/Graph.c.s

.PHONY : src/main/Graph.s

# target to generate assembly for a file
src/main/Graph.c.s:
	$(MAKE) -f CMakeFiles/myGraph.dir/build.make CMakeFiles/myGraph.dir/src/main/Graph.c.s
.PHONY : src/main/Graph.c.s

src/main/Z3Tools.o: src/main/Z3Tools.c.o

.PHONY : src/main/Z3Tools.o

# target to build an object file
src/main/Z3Tools.c.o:
	$(MAKE) -f CMakeFiles/myZ3.dir/build.make CMakeFiles/myZ3.dir/src/main/Z3Tools.c.o
.PHONY : src/main/Z3Tools.c.o

src/main/Z3Tools.i: src/main/Z3Tools.c.i

.PHONY : src/main/Z3Tools.i

# target to preprocess a source file
src/main/Z3Tools.c.i:
	$(MAKE) -f CMakeFiles/myZ3.dir/build.make CMakeFiles/myZ3.dir/src/main/Z3Tools.c.i
.PHONY : src/main/Z3Tools.c.i

src/main/Z3Tools.s: src/main/Z3Tools.c.s

.PHONY : src/main/Z3Tools.s

# target to generate assembly for a file
src/main/Z3Tools.c.s:
	$(MAKE) -f CMakeFiles/myZ3.dir/build.make CMakeFiles/myZ3.dir/src/main/Z3Tools.c.s
.PHONY : src/main/Z3Tools.c.s

src/main/main.o: src/main/main.c.o

.PHONY : src/main/main.o

# target to build an object file
src/main/main.c.o:
	$(MAKE) -f CMakeFiles/graphProblemSolver.dir/build.make CMakeFiles/graphProblemSolver.dir/src/main/main.c.o
.PHONY : src/main/main.c.o

src/main/main.i: src/main/main.c.i

.PHONY : src/main/main.i

# target to preprocess a source file
src/main/main.c.i:
	$(MAKE) -f CMakeFiles/graphProblemSolver.dir/build.make CMakeFiles/graphProblemSolver.dir/src/main/main.c.i
.PHONY : src/main/main.c.i

src/main/main.s: src/main/main.c.s

.PHONY : src/main/main.s

# target to generate assembly for a file
src/main/main.c.s:
	$(MAKE) -f CMakeFiles/graphProblemSolver.dir/build.make CMakeFiles/graphProblemSolver.dir/src/main/main.c.s
.PHONY : src/main/main.c.s

src/parser/src/EdgeList.o: src/parser/src/EdgeList.c.o

.PHONY : src/parser/src/EdgeList.o

# target to build an object file
src/parser/src/EdgeList.c.o:
	$(MAKE) -f CMakeFiles/parser.dir/build.make CMakeFiles/parser.dir/src/parser/src/EdgeList.c.o
.PHONY : src/parser/src/EdgeList.c.o

src/parser/src/EdgeList.i: src/parser/src/EdgeList.c.i

.PHONY : src/parser/src/EdgeList.i

# target to preprocess a source file
src/parser/src/EdgeList.c.i:
	$(MAKE) -f CMakeFiles/parser.dir/build.make CMakeFiles/parser.dir/src/parser/src/EdgeList.c.i
.PHONY : src/parser/src/EdgeList.c.i

src/parser/src/EdgeList.s: src/parser/src/EdgeList.c.s

.PHONY : src/parser/src/EdgeList.s

# target to generate assembly for a file
src/parser/src/EdgeList.c.s:
	$(MAKE) -f CMakeFiles/parser.dir/build.make CMakeFiles/parser.dir/src/parser/src/EdgeList.c.s
.PHONY : src/parser/src/EdgeList.c.s

src/parser/src/GraphListToGraph.o: src/parser/src/GraphListToGraph.c.o

.PHONY : src/parser/src/GraphListToGraph.o

# target to build an object file
src/parser/src/GraphListToGraph.c.o:
	$(MAKE) -f CMakeFiles/parser.dir/build.make CMakeFiles/parser.dir/src/parser/src/GraphListToGraph.c.o
.PHONY : src/parser/src/GraphListToGraph.c.o

src/parser/src/GraphListToGraph.i: src/parser/src/GraphListToGraph.c.i

.PHONY : src/parser/src/GraphListToGraph.i

# target to preprocess a source file
src/parser/src/GraphListToGraph.c.i:
	$(MAKE) -f CMakeFiles/parser.dir/build.make CMakeFiles/parser.dir/src/parser/src/GraphListToGraph.c.i
.PHONY : src/parser/src/GraphListToGraph.c.i

src/parser/src/GraphListToGraph.s: src/parser/src/GraphListToGraph.c.s

.PHONY : src/parser/src/GraphListToGraph.s

# target to generate assembly for a file
src/parser/src/GraphListToGraph.c.s:
	$(MAKE) -f CMakeFiles/parser.dir/build.make CMakeFiles/parser.dir/src/parser/src/GraphListToGraph.c.s
.PHONY : src/parser/src/GraphListToGraph.c.s

src/parser/src/NodeList.o: src/parser/src/NodeList.c.o

.PHONY : src/parser/src/NodeList.o

# target to build an object file
src/parser/src/NodeList.c.o:
	$(MAKE) -f CMakeFiles/parser.dir/build.make CMakeFiles/parser.dir/src/parser/src/NodeList.c.o
.PHONY : src/parser/src/NodeList.c.o

src/parser/src/NodeList.i: src/parser/src/NodeList.c.i

.PHONY : src/parser/src/NodeList.i

# target to preprocess a source file
src/parser/src/NodeList.c.i:
	$(MAKE) -f CMakeFiles/parser.dir/build.make CMakeFiles/parser.dir/src/parser/src/NodeList.c.i
.PHONY : src/parser/src/NodeList.c.i

src/parser/src/NodeList.s: src/parser/src/NodeList.c.s

.PHONY : src/parser/src/NodeList.s

# target to generate assembly for a file
src/parser/src/NodeList.c.s:
	$(MAKE) -f CMakeFiles/parser.dir/build.make CMakeFiles/parser.dir/src/parser/src/NodeList.c.s
.PHONY : src/parser/src/NodeList.c.s

src/parser/src/Parsing.o: src/parser/src/Parsing.c.o

.PHONY : src/parser/src/Parsing.o

# target to build an object file
src/parser/src/Parsing.c.o:
	$(MAKE) -f CMakeFiles/parser.dir/build.make CMakeFiles/parser.dir/src/parser/src/Parsing.c.o
.PHONY : src/parser/src/Parsing.c.o

src/parser/src/Parsing.i: src/parser/src/Parsing.c.i

.PHONY : src/parser/src/Parsing.i

# target to preprocess a source file
src/parser/src/Parsing.c.i:
	$(MAKE) -f CMakeFiles/parser.dir/build.make CMakeFiles/parser.dir/src/parser/src/Parsing.c.i
.PHONY : src/parser/src/Parsing.c.i

src/parser/src/Parsing.s: src/parser/src/Parsing.c.s

.PHONY : src/parser/src/Parsing.s

# target to generate assembly for a file
src/parser/src/Parsing.c.s:
	$(MAKE) -f CMakeFiles/parser.dir/build.make CMakeFiles/parser.dir/src/parser/src/Parsing.c.s
.PHONY : src/parser/src/Parsing.c.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... graphParser"
	@echo "... graphProblemSolver"
	@echo "... biCon"
	@echo "... rebuild_cache"
	@echo "... Z3Example"
	@echo "... parser"
	@echo "... myZ3"
	@echo "... edit_cache"
	@echo "... myGraph"
	@echo "... Lexer.o"
	@echo "... Lexer.i"
	@echo "... Lexer.s"
	@echo "... Parser.o"
	@echo "... Parser.i"
	@echo "... Parser.s"
	@echo "... examples/Z3Example.o"
	@echo "... examples/Z3Example.i"
	@echo "... examples/Z3Example.s"
	@echo "... examples/graphUsage.o"
	@echo "... examples/graphUsage.i"
	@echo "... examples/graphUsage.s"
	@echo "... src/EdgeConProblem/EdgeConGraph.o"
	@echo "... src/EdgeConProblem/EdgeConGraph.i"
	@echo "... src/EdgeConProblem/EdgeConGraph.s"
	@echo "... src/EdgeConProblem/EdgeConReduction.o"
	@echo "... src/EdgeConProblem/EdgeConReduction.i"
	@echo "... src/EdgeConProblem/EdgeConReduction.s"
	@echo "... src/EdgeConProblem/EdgeConResolution.o"
	@echo "... src/EdgeConProblem/EdgeConResolution.i"
	@echo "... src/EdgeConProblem/EdgeConResolution.s"
	@echo "... src/main/Graph.o"
	@echo "... src/main/Graph.i"
	@echo "... src/main/Graph.s"
	@echo "... src/main/Z3Tools.o"
	@echo "... src/main/Z3Tools.i"
	@echo "... src/main/Z3Tools.s"
	@echo "... src/main/main.o"
	@echo "... src/main/main.i"
	@echo "... src/main/main.s"
	@echo "... src/parser/src/EdgeList.o"
	@echo "... src/parser/src/EdgeList.i"
	@echo "... src/parser/src/EdgeList.s"
	@echo "... src/parser/src/GraphListToGraph.o"
	@echo "... src/parser/src/GraphListToGraph.i"
	@echo "... src/parser/src/GraphListToGraph.s"
	@echo "... src/parser/src/NodeList.o"
	@echo "... src/parser/src/NodeList.i"
	@echo "... src/parser/src/NodeList.s"
	@echo "... src/parser/src/Parsing.o"
	@echo "... src/parser/src/Parsing.i"
	@echo "... src/parser/src/Parsing.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

