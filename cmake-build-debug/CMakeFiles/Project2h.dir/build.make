# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.16

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Users\James Xia\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\201.7846.88\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Users\James Xia\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\201.7846.88\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\Users\James Xia\Desktop\temp"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\James Xia\Desktop\temp\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/Project2h.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Project2h.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Project2h.dir/flags.make

CMakeFiles/Project2h.dir/main.cpp.obj: CMakeFiles/Project2h.dir/flags.make
CMakeFiles/Project2h.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\James Xia\Desktop\temp\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Project2h.dir/main.cpp.obj"
	D:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Project2h.dir\main.cpp.obj -c "C:\Users\James Xia\Desktop\temp\main.cpp"

CMakeFiles/Project2h.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Project2h.dir/main.cpp.i"
	D:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\James Xia\Desktop\temp\main.cpp" > CMakeFiles\Project2h.dir\main.cpp.i

CMakeFiles/Project2h.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Project2h.dir/main.cpp.s"
	D:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\James Xia\Desktop\temp\main.cpp" -o CMakeFiles\Project2h.dir\main.cpp.s

CMakeFiles/Project2h.dir/simulation.cpp.obj: CMakeFiles/Project2h.dir/flags.make
CMakeFiles/Project2h.dir/simulation.cpp.obj: ../simulation.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\James Xia\Desktop\temp\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Project2h.dir/simulation.cpp.obj"
	D:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Project2h.dir\simulation.cpp.obj -c "C:\Users\James Xia\Desktop\temp\simulation.cpp"

CMakeFiles/Project2h.dir/simulation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Project2h.dir/simulation.cpp.i"
	D:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\James Xia\Desktop\temp\simulation.cpp" > CMakeFiles\Project2h.dir\simulation.cpp.i

CMakeFiles/Project2h.dir/simulation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Project2h.dir/simulation.cpp.s"
	D:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\James Xia\Desktop\temp\simulation.cpp" -o CMakeFiles\Project2h.dir\simulation.cpp.s

# Object files for target Project2h
Project2h_OBJECTS = \
"CMakeFiles/Project2h.dir/main.cpp.obj" \
"CMakeFiles/Project2h.dir/simulation.cpp.obj"

# External object files for target Project2h
Project2h_EXTERNAL_OBJECTS =

Project2h.exe: CMakeFiles/Project2h.dir/main.cpp.obj
Project2h.exe: CMakeFiles/Project2h.dir/simulation.cpp.obj
Project2h.exe: CMakeFiles/Project2h.dir/build.make
Project2h.exe: CMakeFiles/Project2h.dir/linklibs.rsp
Project2h.exe: CMakeFiles/Project2h.dir/objects1.rsp
Project2h.exe: CMakeFiles/Project2h.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\Users\James Xia\Desktop\temp\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable Project2h.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Project2h.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Project2h.dir/build: Project2h.exe

.PHONY : CMakeFiles/Project2h.dir/build

CMakeFiles/Project2h.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Project2h.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Project2h.dir/clean

CMakeFiles/Project2h.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\Users\James Xia\Desktop\temp" "C:\Users\James Xia\Desktop\temp" "C:\Users\James Xia\Desktop\temp\cmake-build-debug" "C:\Users\James Xia\Desktop\temp\cmake-build-debug" "C:\Users\James Xia\Desktop\temp\cmake-build-debug\CMakeFiles\Project2h.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Project2h.dir/depend
