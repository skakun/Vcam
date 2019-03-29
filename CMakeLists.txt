cmake_minimum_required(VERSION 3.6)   # CMake version check
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)
set(EXECUTABLE_OUTPUT_PATH bin)
project(vcam)               # Create project "simple_example"
#set(CMAKE_CXX_STANDARD 11)            # Enable c++11 standard
#set(CMAKE_C_FLAGS "std=c99")
find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

set(CMAKE_C_COMPILER "/usr/bin/gcc")
set(LIBS )
set(SOURCE_FILES src/main.cpp src/Solid/Solid.cpp src/SolidParser/JsonParser.cpp src/WorldTransformer/WorldTransformer.cpp src/Camera/Camera.cpp)            # Add main.cpp file of project root directory as source file
add_executable(vcam  ${SOURCE_FILES})       # Add executable target with source files listed in SOURCE_FILES variable
target_link_libraries (vcam  ${LIBS})
