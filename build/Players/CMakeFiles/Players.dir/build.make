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
CMAKE_COMMAND = /snap/cmake/1445/bin/cmake

# The command to remove a file.
RM = /snap/cmake/1445/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/kubik/IU5-Monopoly

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kubik/IU5-Monopoly/build

# Include any dependencies generated for this target.
include Players/CMakeFiles/Players.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include Players/CMakeFiles/Players.dir/compiler_depend.make

# Include the progress variables for this target.
include Players/CMakeFiles/Players.dir/progress.make

# Include the compile flags for this target's objects.
include Players/CMakeFiles/Players.dir/flags.make

Players/CMakeFiles/Players.dir/codegen:
.PHONY : Players/CMakeFiles/Players.dir/codegen

Players/CMakeFiles/Players.dir/Dice.cpp.o: Players/CMakeFiles/Players.dir/flags.make
Players/CMakeFiles/Players.dir/Dice.cpp.o: /home/kubik/IU5-Monopoly/Players/Dice.cpp
Players/CMakeFiles/Players.dir/Dice.cpp.o: Players/CMakeFiles/Players.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/kubik/IU5-Monopoly/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object Players/CMakeFiles/Players.dir/Dice.cpp.o"
	cd /home/kubik/IU5-Monopoly/build/Players && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT Players/CMakeFiles/Players.dir/Dice.cpp.o -MF CMakeFiles/Players.dir/Dice.cpp.o.d -o CMakeFiles/Players.dir/Dice.cpp.o -c /home/kubik/IU5-Monopoly/Players/Dice.cpp

Players/CMakeFiles/Players.dir/Dice.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Players.dir/Dice.cpp.i"
	cd /home/kubik/IU5-Monopoly/build/Players && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kubik/IU5-Monopoly/Players/Dice.cpp > CMakeFiles/Players.dir/Dice.cpp.i

Players/CMakeFiles/Players.dir/Dice.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Players.dir/Dice.cpp.s"
	cd /home/kubik/IU5-Monopoly/build/Players && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kubik/IU5-Monopoly/Players/Dice.cpp -o CMakeFiles/Players.dir/Dice.cpp.s

Players/CMakeFiles/Players.dir/GameLogic.cpp.o: Players/CMakeFiles/Players.dir/flags.make
Players/CMakeFiles/Players.dir/GameLogic.cpp.o: /home/kubik/IU5-Monopoly/Players/GameLogic.cpp
Players/CMakeFiles/Players.dir/GameLogic.cpp.o: Players/CMakeFiles/Players.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/kubik/IU5-Monopoly/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object Players/CMakeFiles/Players.dir/GameLogic.cpp.o"
	cd /home/kubik/IU5-Monopoly/build/Players && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT Players/CMakeFiles/Players.dir/GameLogic.cpp.o -MF CMakeFiles/Players.dir/GameLogic.cpp.o.d -o CMakeFiles/Players.dir/GameLogic.cpp.o -c /home/kubik/IU5-Monopoly/Players/GameLogic.cpp

Players/CMakeFiles/Players.dir/GameLogic.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Players.dir/GameLogic.cpp.i"
	cd /home/kubik/IU5-Monopoly/build/Players && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kubik/IU5-Monopoly/Players/GameLogic.cpp > CMakeFiles/Players.dir/GameLogic.cpp.i

Players/CMakeFiles/Players.dir/GameLogic.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Players.dir/GameLogic.cpp.s"
	cd /home/kubik/IU5-Monopoly/build/Players && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kubik/IU5-Monopoly/Players/GameLogic.cpp -o CMakeFiles/Players.dir/GameLogic.cpp.s

Players/CMakeFiles/Players.dir/Player.cpp.o: Players/CMakeFiles/Players.dir/flags.make
Players/CMakeFiles/Players.dir/Player.cpp.o: /home/kubik/IU5-Monopoly/Players/Player.cpp
Players/CMakeFiles/Players.dir/Player.cpp.o: Players/CMakeFiles/Players.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/kubik/IU5-Monopoly/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object Players/CMakeFiles/Players.dir/Player.cpp.o"
	cd /home/kubik/IU5-Monopoly/build/Players && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT Players/CMakeFiles/Players.dir/Player.cpp.o -MF CMakeFiles/Players.dir/Player.cpp.o.d -o CMakeFiles/Players.dir/Player.cpp.o -c /home/kubik/IU5-Monopoly/Players/Player.cpp

Players/CMakeFiles/Players.dir/Player.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Players.dir/Player.cpp.i"
	cd /home/kubik/IU5-Monopoly/build/Players && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kubik/IU5-Monopoly/Players/Player.cpp > CMakeFiles/Players.dir/Player.cpp.i

Players/CMakeFiles/Players.dir/Player.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Players.dir/Player.cpp.s"
	cd /home/kubik/IU5-Monopoly/build/Players && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kubik/IU5-Monopoly/Players/Player.cpp -o CMakeFiles/Players.dir/Player.cpp.s

# Object files for target Players
Players_OBJECTS = \
"CMakeFiles/Players.dir/Dice.cpp.o" \
"CMakeFiles/Players.dir/GameLogic.cpp.o" \
"CMakeFiles/Players.dir/Player.cpp.o"

# External object files for target Players
Players_EXTERNAL_OBJECTS =

Players/libPlayers.a: Players/CMakeFiles/Players.dir/Dice.cpp.o
Players/libPlayers.a: Players/CMakeFiles/Players.dir/GameLogic.cpp.o
Players/libPlayers.a: Players/CMakeFiles/Players.dir/Player.cpp.o
Players/libPlayers.a: Players/CMakeFiles/Players.dir/build.make
Players/libPlayers.a: Players/CMakeFiles/Players.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/kubik/IU5-Monopoly/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX static library libPlayers.a"
	cd /home/kubik/IU5-Monopoly/build/Players && $(CMAKE_COMMAND) -P CMakeFiles/Players.dir/cmake_clean_target.cmake
	cd /home/kubik/IU5-Monopoly/build/Players && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Players.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Players/CMakeFiles/Players.dir/build: Players/libPlayers.a
.PHONY : Players/CMakeFiles/Players.dir/build

Players/CMakeFiles/Players.dir/clean:
	cd /home/kubik/IU5-Monopoly/build/Players && $(CMAKE_COMMAND) -P CMakeFiles/Players.dir/cmake_clean.cmake
.PHONY : Players/CMakeFiles/Players.dir/clean

Players/CMakeFiles/Players.dir/depend:
	cd /home/kubik/IU5-Monopoly/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kubik/IU5-Monopoly /home/kubik/IU5-Monopoly/Players /home/kubik/IU5-Monopoly/build /home/kubik/IU5-Monopoly/build/Players /home/kubik/IU5-Monopoly/build/Players/CMakeFiles/Players.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : Players/CMakeFiles/Players.dir/depend

