# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.18

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\dev\mp3_encoder

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\dev\mp3_encoder

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	"C:\Program Files\CMake\bin\cmake-gui.exe" -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	"C:\Program Files\CMake\bin\cmake.exe" --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start C:\dev\mp3_encoder\CMakeFiles C:\dev\mp3_encoder\\CMakeFiles\progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles\Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start C:\dev\mp3_encoder\CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles\Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles\Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named pthreads-win32-build

# Build rule for target.
pthreads-win32-build: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles\Makefile2 pthreads-win32-build
.PHONY : pthreads-win32-build

# fast build rule for target.
pthreads-win32-build/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\pthreads-win32-build.dir\build.make CMakeFiles/pthreads-win32-build.dir/build
.PHONY : pthreads-win32-build/fast

#=============================================================================
# Target rules for targets named lame-build

# Build rule for target.
lame-build: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles\Makefile2 lame-build
.PHONY : lame-build

# fast build rule for target.
lame-build/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\lame-build.dir\build.make CMakeFiles/lame-build.dir/build
.PHONY : lame-build/fast

#=============================================================================
# Target rules for targets named mp3_encoder

# Build rule for target.
mp3_encoder: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles\Makefile2 mp3_encoder
.PHONY : mp3_encoder

# fast build rule for target.
mp3_encoder/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\mp3_encoder.dir\build.make CMakeFiles/mp3_encoder.dir/build
.PHONY : mp3_encoder/fast

src/main.obj: src/main.cpp.obj

.PHONY : src/main.obj

# target to build an object file
src/main.cpp.obj:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\mp3_encoder.dir\build.make CMakeFiles/mp3_encoder.dir/src/main.cpp.obj
.PHONY : src/main.cpp.obj

src/main.i: src/main.cpp.i

.PHONY : src/main.i

# target to preprocess a source file
src/main.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\mp3_encoder.dir\build.make CMakeFiles/mp3_encoder.dir/src/main.cpp.i
.PHONY : src/main.cpp.i

src/main.s: src/main.cpp.s

.PHONY : src/main.s

# target to generate assembly for a file
src/main.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\mp3_encoder.dir\build.make CMakeFiles/mp3_encoder.dir/src/main.cpp.s
.PHONY : src/main.cpp.s

src/thread_handler.obj: src/thread_handler.cpp.obj

.PHONY : src/thread_handler.obj

# target to build an object file
src/thread_handler.cpp.obj:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\mp3_encoder.dir\build.make CMakeFiles/mp3_encoder.dir/src/thread_handler.cpp.obj
.PHONY : src/thread_handler.cpp.obj

src/thread_handler.i: src/thread_handler.cpp.i

.PHONY : src/thread_handler.i

# target to preprocess a source file
src/thread_handler.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\mp3_encoder.dir\build.make CMakeFiles/mp3_encoder.dir/src/thread_handler.cpp.i
.PHONY : src/thread_handler.cpp.i

src/thread_handler.s: src/thread_handler.cpp.s

.PHONY : src/thread_handler.s

# target to generate assembly for a file
src/thread_handler.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\mp3_encoder.dir\build.make CMakeFiles/mp3_encoder.dir/src/thread_handler.cpp.s
.PHONY : src/thread_handler.cpp.s

src/wav.obj: src/wav.cpp.obj

.PHONY : src/wav.obj

# target to build an object file
src/wav.cpp.obj:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\mp3_encoder.dir\build.make CMakeFiles/mp3_encoder.dir/src/wav.cpp.obj
.PHONY : src/wav.cpp.obj

src/wav.i: src/wav.cpp.i

.PHONY : src/wav.i

# target to preprocess a source file
src/wav.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\mp3_encoder.dir\build.make CMakeFiles/mp3_encoder.dir/src/wav.cpp.i
.PHONY : src/wav.cpp.i

src/wav.s: src/wav.cpp.s

.PHONY : src/wav.s

# target to generate assembly for a file
src/wav.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\mp3_encoder.dir\build.make CMakeFiles/mp3_encoder.dir/src/wav.cpp.s
.PHONY : src/wav.cpp.s

# Help Target
help:
	@echo The following are some of the valid targets for this Makefile:
	@echo ... all (the default if no target is provided)
	@echo ... clean
	@echo ... depend
	@echo ... edit_cache
	@echo ... rebuild_cache
	@echo ... lame-build
	@echo ... pthreads-win32-build
	@echo ... mp3_encoder
	@echo ... src/main.obj
	@echo ... src/main.i
	@echo ... src/main.s
	@echo ... src/thread_handler.obj
	@echo ... src/thread_handler.i
	@echo ... src/thread_handler.s
	@echo ... src/wav.obj
	@echo ... src/wav.i
	@echo ... src/wav.s
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles\Makefile.cmake 0
.PHONY : cmake_check_build_system

