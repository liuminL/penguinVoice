# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /Music/qr_voice/micro/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Music/qr_voice/micro/build

# Include any dependencies generated for this target.
include hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/depend.make

# Include the progress variables for this target.
include hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/progress.make

# Include the compile flags for this target's objects.
include hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/flags.make

hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/hori_voicecenter.cpp.o: hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/flags.make
hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/hori_voicecenter.cpp.o: /Music/qr_voice/micro/src/hori_voicecenter/src/hori_voicecenter.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Music/qr_voice/micro/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/hori_voicecenter.cpp.o"
	cd /Music/qr_voice/micro/build/hori_voicecenter && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/hori_voicecenter_node.dir/src/hori_voicecenter.cpp.o -c /Music/qr_voice/micro/src/hori_voicecenter/src/hori_voicecenter.cpp

hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/hori_voicecenter.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hori_voicecenter_node.dir/src/hori_voicecenter.cpp.i"
	cd /Music/qr_voice/micro/build/hori_voicecenter && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Music/qr_voice/micro/src/hori_voicecenter/src/hori_voicecenter.cpp > CMakeFiles/hori_voicecenter_node.dir/src/hori_voicecenter.cpp.i

hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/hori_voicecenter.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hori_voicecenter_node.dir/src/hori_voicecenter.cpp.s"
	cd /Music/qr_voice/micro/build/hori_voicecenter && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Music/qr_voice/micro/src/hori_voicecenter/src/hori_voicecenter.cpp -o CMakeFiles/hori_voicecenter_node.dir/src/hori_voicecenter.cpp.s

hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/hori_voicecenter.cpp.o.requires:

.PHONY : hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/hori_voicecenter.cpp.o.requires

hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/hori_voicecenter.cpp.o.provides: hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/hori_voicecenter.cpp.o.requires
	$(MAKE) -f hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/build.make hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/hori_voicecenter.cpp.o.provides.build
.PHONY : hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/hori_voicecenter.cpp.o.provides

hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/hori_voicecenter.cpp.o.provides.build: hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/hori_voicecenter.cpp.o


hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/client/hori_centreClient.cpp.o: hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/flags.make
hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/client/hori_centreClient.cpp.o: /Music/qr_voice/micro/src/hori_voicecenter/src/client/hori_centreClient.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Music/qr_voice/micro/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/client/hori_centreClient.cpp.o"
	cd /Music/qr_voice/micro/build/hori_voicecenter && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/hori_voicecenter_node.dir/src/client/hori_centreClient.cpp.o -c /Music/qr_voice/micro/src/hori_voicecenter/src/client/hori_centreClient.cpp

hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/client/hori_centreClient.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hori_voicecenter_node.dir/src/client/hori_centreClient.cpp.i"
	cd /Music/qr_voice/micro/build/hori_voicecenter && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Music/qr_voice/micro/src/hori_voicecenter/src/client/hori_centreClient.cpp > CMakeFiles/hori_voicecenter_node.dir/src/client/hori_centreClient.cpp.i

hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/client/hori_centreClient.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hori_voicecenter_node.dir/src/client/hori_centreClient.cpp.s"
	cd /Music/qr_voice/micro/build/hori_voicecenter && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Music/qr_voice/micro/src/hori_voicecenter/src/client/hori_centreClient.cpp -o CMakeFiles/hori_voicecenter_node.dir/src/client/hori_centreClient.cpp.s

hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/client/hori_centreClient.cpp.o.requires:

.PHONY : hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/client/hori_centreClient.cpp.o.requires

hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/client/hori_centreClient.cpp.o.provides: hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/client/hori_centreClient.cpp.o.requires
	$(MAKE) -f hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/build.make hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/client/hori_centreClient.cpp.o.provides.build
.PHONY : hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/client/hori_centreClient.cpp.o.provides

hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/client/hori_centreClient.cpp.o.provides.build: hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/client/hori_centreClient.cpp.o


hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/client/loadCfg.cpp.o: hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/flags.make
hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/client/loadCfg.cpp.o: /Music/qr_voice/micro/src/hori_voicecenter/src/client/loadCfg.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Music/qr_voice/micro/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/client/loadCfg.cpp.o"
	cd /Music/qr_voice/micro/build/hori_voicecenter && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/hori_voicecenter_node.dir/src/client/loadCfg.cpp.o -c /Music/qr_voice/micro/src/hori_voicecenter/src/client/loadCfg.cpp

hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/client/loadCfg.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hori_voicecenter_node.dir/src/client/loadCfg.cpp.i"
	cd /Music/qr_voice/micro/build/hori_voicecenter && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Music/qr_voice/micro/src/hori_voicecenter/src/client/loadCfg.cpp > CMakeFiles/hori_voicecenter_node.dir/src/client/loadCfg.cpp.i

hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/client/loadCfg.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hori_voicecenter_node.dir/src/client/loadCfg.cpp.s"
	cd /Music/qr_voice/micro/build/hori_voicecenter && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Music/qr_voice/micro/src/hori_voicecenter/src/client/loadCfg.cpp -o CMakeFiles/hori_voicecenter_node.dir/src/client/loadCfg.cpp.s

hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/client/loadCfg.cpp.o.requires:

.PHONY : hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/client/loadCfg.cpp.o.requires

hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/client/loadCfg.cpp.o.provides: hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/client/loadCfg.cpp.o.requires
	$(MAKE) -f hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/build.make hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/client/loadCfg.cpp.o.provides.build
.PHONY : hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/client/loadCfg.cpp.o.provides

hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/client/loadCfg.cpp.o.provides.build: hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/client/loadCfg.cpp.o


hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/client/json/json_reader.cpp.o: hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/flags.make
hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/client/json/json_reader.cpp.o: /Music/qr_voice/micro/src/hori_voicecenter/src/client/json/json_reader.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Music/qr_voice/micro/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/client/json/json_reader.cpp.o"
	cd /Music/qr_voice/micro/build/hori_voicecenter && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/hori_voicecenter_node.dir/src/client/json/json_reader.cpp.o -c /Music/qr_voice/micro/src/hori_voicecenter/src/client/json/json_reader.cpp

hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/client/json/json_reader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hori_voicecenter_node.dir/src/client/json/json_reader.cpp.i"
	cd /Music/qr_voice/micro/build/hori_voicecenter && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Music/qr_voice/micro/src/hori_voicecenter/src/client/json/json_reader.cpp > CMakeFiles/hori_voicecenter_node.dir/src/client/json/json_reader.cpp.i

hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/client/json/json_reader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hori_voicecenter_node.dir/src/client/json/json_reader.cpp.s"
	cd /Music/qr_voice/micro/build/hori_voicecenter && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Music/qr_voice/micro/src/hori_voicecenter/src/client/json/json_reader.cpp -o CMakeFiles/hori_voicecenter_node.dir/src/client/json/json_reader.cpp.s

hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/client/json/json_reader.cpp.o.requires:

.PHONY : hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/client/json/json_reader.cpp.o.requires

hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/client/json/json_reader.cpp.o.provides: hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/client/json/json_reader.cpp.o.requires
	$(MAKE) -f hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/build.make hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/client/json/json_reader.cpp.o.provides.build
.PHONY : hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/client/json/json_reader.cpp.o.provides

hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/client/json/json_reader.cpp.o.provides.build: hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/client/json/json_reader.cpp.o


hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/client/json/json_value.cpp.o: hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/flags.make
hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/client/json/json_value.cpp.o: /Music/qr_voice/micro/src/hori_voicecenter/src/client/json/json_value.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Music/qr_voice/micro/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/client/json/json_value.cpp.o"
	cd /Music/qr_voice/micro/build/hori_voicecenter && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/hori_voicecenter_node.dir/src/client/json/json_value.cpp.o -c /Music/qr_voice/micro/src/hori_voicecenter/src/client/json/json_value.cpp

hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/client/json/json_value.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hori_voicecenter_node.dir/src/client/json/json_value.cpp.i"
	cd /Music/qr_voice/micro/build/hori_voicecenter && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Music/qr_voice/micro/src/hori_voicecenter/src/client/json/json_value.cpp > CMakeFiles/hori_voicecenter_node.dir/src/client/json/json_value.cpp.i

hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/client/json/json_value.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hori_voicecenter_node.dir/src/client/json/json_value.cpp.s"
	cd /Music/qr_voice/micro/build/hori_voicecenter && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Music/qr_voice/micro/src/hori_voicecenter/src/client/json/json_value.cpp -o CMakeFiles/hori_voicecenter_node.dir/src/client/json/json_value.cpp.s

hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/client/json/json_value.cpp.o.requires:

.PHONY : hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/client/json/json_value.cpp.o.requires

hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/client/json/json_value.cpp.o.provides: hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/client/json/json_value.cpp.o.requires
	$(MAKE) -f hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/build.make hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/client/json/json_value.cpp.o.provides.build
.PHONY : hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/client/json/json_value.cpp.o.provides

hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/client/json/json_value.cpp.o.provides.build: hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/client/json/json_value.cpp.o


hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/client/json/json_writer.cpp.o: hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/flags.make
hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/client/json/json_writer.cpp.o: /Music/qr_voice/micro/src/hori_voicecenter/src/client/json/json_writer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Music/qr_voice/micro/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/client/json/json_writer.cpp.o"
	cd /Music/qr_voice/micro/build/hori_voicecenter && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/hori_voicecenter_node.dir/src/client/json/json_writer.cpp.o -c /Music/qr_voice/micro/src/hori_voicecenter/src/client/json/json_writer.cpp

hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/client/json/json_writer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hori_voicecenter_node.dir/src/client/json/json_writer.cpp.i"
	cd /Music/qr_voice/micro/build/hori_voicecenter && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Music/qr_voice/micro/src/hori_voicecenter/src/client/json/json_writer.cpp > CMakeFiles/hori_voicecenter_node.dir/src/client/json/json_writer.cpp.i

hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/client/json/json_writer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hori_voicecenter_node.dir/src/client/json/json_writer.cpp.s"
	cd /Music/qr_voice/micro/build/hori_voicecenter && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Music/qr_voice/micro/src/hori_voicecenter/src/client/json/json_writer.cpp -o CMakeFiles/hori_voicecenter_node.dir/src/client/json/json_writer.cpp.s

hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/client/json/json_writer.cpp.o.requires:

.PHONY : hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/client/json/json_writer.cpp.o.requires

hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/client/json/json_writer.cpp.o.provides: hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/client/json/json_writer.cpp.o.requires
	$(MAKE) -f hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/build.make hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/client/json/json_writer.cpp.o.provides.build
.PHONY : hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/client/json/json_writer.cpp.o.provides

hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/client/json/json_writer.cpp.o.provides.build: hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/client/json/json_writer.cpp.o


# Object files for target hori_voicecenter_node
hori_voicecenter_node_OBJECTS = \
"CMakeFiles/hori_voicecenter_node.dir/src/hori_voicecenter.cpp.o" \
"CMakeFiles/hori_voicecenter_node.dir/src/client/hori_centreClient.cpp.o" \
"CMakeFiles/hori_voicecenter_node.dir/src/client/loadCfg.cpp.o" \
"CMakeFiles/hori_voicecenter_node.dir/src/client/json/json_reader.cpp.o" \
"CMakeFiles/hori_voicecenter_node.dir/src/client/json/json_value.cpp.o" \
"CMakeFiles/hori_voicecenter_node.dir/src/client/json/json_writer.cpp.o"

# External object files for target hori_voicecenter_node
hori_voicecenter_node_EXTERNAL_OBJECTS =

/Music/qr_voice/micro/devel/lib/hori_voicecenter/hori_voicecenter_node: hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/hori_voicecenter.cpp.o
/Music/qr_voice/micro/devel/lib/hori_voicecenter/hori_voicecenter_node: hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/client/hori_centreClient.cpp.o
/Music/qr_voice/micro/devel/lib/hori_voicecenter/hori_voicecenter_node: hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/client/loadCfg.cpp.o
/Music/qr_voice/micro/devel/lib/hori_voicecenter/hori_voicecenter_node: hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/client/json/json_reader.cpp.o
/Music/qr_voice/micro/devel/lib/hori_voicecenter/hori_voicecenter_node: hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/client/json/json_value.cpp.o
/Music/qr_voice/micro/devel/lib/hori_voicecenter/hori_voicecenter_node: hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/client/json/json_writer.cpp.o
/Music/qr_voice/micro/devel/lib/hori_voicecenter/hori_voicecenter_node: hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/build.make
/Music/qr_voice/micro/devel/lib/hori_voicecenter/hori_voicecenter_node: /opt/ros/kinetic/lib/libroscpp.so
/Music/qr_voice/micro/devel/lib/hori_voicecenter/hori_voicecenter_node: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
/Music/qr_voice/micro/devel/lib/hori_voicecenter/hori_voicecenter_node: /usr/lib/x86_64-linux-gnu/libboost_signals.so
/Music/qr_voice/micro/devel/lib/hori_voicecenter/hori_voicecenter_node: /opt/ros/kinetic/lib/librosconsole.so
/Music/qr_voice/micro/devel/lib/hori_voicecenter/hori_voicecenter_node: /opt/ros/kinetic/lib/librosconsole_log4cxx.so
/Music/qr_voice/micro/devel/lib/hori_voicecenter/hori_voicecenter_node: /opt/ros/kinetic/lib/librosconsole_backend_interface.so
/Music/qr_voice/micro/devel/lib/hori_voicecenter/hori_voicecenter_node: /usr/lib/x86_64-linux-gnu/liblog4cxx.so
/Music/qr_voice/micro/devel/lib/hori_voicecenter/hori_voicecenter_node: /usr/lib/x86_64-linux-gnu/libboost_regex.so
/Music/qr_voice/micro/devel/lib/hori_voicecenter/hori_voicecenter_node: /opt/ros/kinetic/lib/libxmlrpcpp.so
/Music/qr_voice/micro/devel/lib/hori_voicecenter/hori_voicecenter_node: /opt/ros/kinetic/lib/libroscpp_serialization.so
/Music/qr_voice/micro/devel/lib/hori_voicecenter/hori_voicecenter_node: /opt/ros/kinetic/lib/librostime.so
/Music/qr_voice/micro/devel/lib/hori_voicecenter/hori_voicecenter_node: /opt/ros/kinetic/lib/libcpp_common.so
/Music/qr_voice/micro/devel/lib/hori_voicecenter/hori_voicecenter_node: /usr/lib/x86_64-linux-gnu/libboost_system.so
/Music/qr_voice/micro/devel/lib/hori_voicecenter/hori_voicecenter_node: /usr/lib/x86_64-linux-gnu/libboost_thread.so
/Music/qr_voice/micro/devel/lib/hori_voicecenter/hori_voicecenter_node: /usr/lib/x86_64-linux-gnu/libboost_chrono.so
/Music/qr_voice/micro/devel/lib/hori_voicecenter/hori_voicecenter_node: /usr/lib/x86_64-linux-gnu/libboost_date_time.so
/Music/qr_voice/micro/devel/lib/hori_voicecenter/hori_voicecenter_node: /usr/lib/x86_64-linux-gnu/libboost_atomic.so
/Music/qr_voice/micro/devel/lib/hori_voicecenter/hori_voicecenter_node: /usr/lib/x86_64-linux-gnu/libpthread.so
/Music/qr_voice/micro/devel/lib/hori_voicecenter/hori_voicecenter_node: /usr/lib/x86_64-linux-gnu/libconsole_bridge.so
/Music/qr_voice/micro/devel/lib/hori_voicecenter/hori_voicecenter_node: hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Music/qr_voice/micro/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable /Music/qr_voice/micro/devel/lib/hori_voicecenter/hori_voicecenter_node"
	cd /Music/qr_voice/micro/build/hori_voicecenter && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/hori_voicecenter_node.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/build: /Music/qr_voice/micro/devel/lib/hori_voicecenter/hori_voicecenter_node

.PHONY : hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/build

hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/requires: hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/hori_voicecenter.cpp.o.requires
hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/requires: hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/client/hori_centreClient.cpp.o.requires
hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/requires: hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/client/loadCfg.cpp.o.requires
hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/requires: hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/client/json/json_reader.cpp.o.requires
hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/requires: hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/client/json/json_value.cpp.o.requires
hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/requires: hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/src/client/json/json_writer.cpp.o.requires

.PHONY : hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/requires

hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/clean:
	cd /Music/qr_voice/micro/build/hori_voicecenter && $(CMAKE_COMMAND) -P CMakeFiles/hori_voicecenter_node.dir/cmake_clean.cmake
.PHONY : hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/clean

hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/depend:
	cd /Music/qr_voice/micro/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Music/qr_voice/micro/src /Music/qr_voice/micro/src/hori_voicecenter /Music/qr_voice/micro/build /Music/qr_voice/micro/build/hori_voicecenter /Music/qr_voice/micro/build/hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : hori_voicecenter/CMakeFiles/hori_voicecenter_node.dir/depend

