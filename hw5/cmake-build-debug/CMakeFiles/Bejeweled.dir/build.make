# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2019.3.3\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2019.3.3\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\CIE\lsolovy\homework\hw5

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\CIE\lsolovy\homework\hw5\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Bejeweled.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Bejeweled.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Bejeweled.dir/flags.make

CMakeFiles/Bejeweled.dir/main.cpp.obj: CMakeFiles/Bejeweled.dir/flags.make
CMakeFiles/Bejeweled.dir/main.cpp.obj: CMakeFiles/Bejeweled.dir/includes_CXX.rsp
CMakeFiles/Bejeweled.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\CIE\lsolovy\homework\hw5\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Bejeweled.dir/main.cpp.obj"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Bejeweled.dir\main.cpp.obj -c C:\CIE\lsolovy\homework\hw5\main.cpp

CMakeFiles/Bejeweled.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Bejeweled.dir/main.cpp.i"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\CIE\lsolovy\homework\hw5\main.cpp > CMakeFiles\Bejeweled.dir\main.cpp.i

CMakeFiles/Bejeweled.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Bejeweled.dir/main.cpp.s"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\CIE\lsolovy\homework\hw5\main.cpp -o CMakeFiles\Bejeweled.dir\main.cpp.s

# Object files for target Bejeweled
Bejeweled_OBJECTS = \
"CMakeFiles/Bejeweled.dir/main.cpp.obj"

# External object files for target Bejeweled
Bejeweled_EXTERNAL_OBJECTS =

Bejeweled.exe: CMakeFiles/Bejeweled.dir/main.cpp.obj
Bejeweled.exe: CMakeFiles/Bejeweled.dir/build.make
Bejeweled.exe: C:/Program\ Files/SFML-2.5.1/lib/libsfml-network-d.a
Bejeweled.exe: C:/Program\ Files/SFML-2.5.1/lib/libsfml-audio-d.a
Bejeweled.exe: C:/Program\ Files/SFML-2.5.1/lib/libsfml-graphics-d.a
Bejeweled.exe: C:/Program\ Files/SFML-2.5.1/lib/libsfml-window-d.a
Bejeweled.exe: C:/Program\ Files/SFML-2.5.1/lib/libsfml-system-d.a
Bejeweled.exe: CMakeFiles/Bejeweled.dir/linklibs.rsp
Bejeweled.exe: CMakeFiles/Bejeweled.dir/objects1.rsp
Bejeweled.exe: CMakeFiles/Bejeweled.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\CIE\lsolovy\homework\hw5\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Bejeweled.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Bejeweled.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Bejeweled.dir/build: Bejeweled.exe

.PHONY : CMakeFiles/Bejeweled.dir/build

CMakeFiles/Bejeweled.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Bejeweled.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Bejeweled.dir/clean

CMakeFiles/Bejeweled.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\CIE\lsolovy\homework\hw5 C:\CIE\lsolovy\homework\hw5 C:\CIE\lsolovy\homework\hw5\cmake-build-debug C:\CIE\lsolovy\homework\hw5\cmake-build-debug C:\CIE\lsolovy\homework\hw5\cmake-build-debug\CMakeFiles\Bejeweled.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Bejeweled.dir/depend

