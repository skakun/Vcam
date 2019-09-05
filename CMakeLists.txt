cmake_minimum_required(VERSION 3.6)   # CMake version check
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)
set(CMAKE_BUILD_TYPE Debug)
#set(EXECUTABLE_OUTPUT_PATH bin)
project(vcam)               # Create project "simple_example"
#set(CMAKE_CXX_STANDARD 11)            # Enable c++11 standard
set(CMAKE_CXX_FLAGS "-fpermissive -std=c++0x")
find_package(Eigen3 REQUIRED)

include_directories(${EIGEN3_INCLUDE_DIR}  ${SFML_INCLUDE_DIR})
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

set(CMAKE_C_COMPILER "/usr/bin/gcc")
set(LIBS sfml-graphics sfml-audio)
set(SOURCE_FILES src/main.cpp src/Figure/Figure.cpp src/SolidParser/JsonParser.cpp src/WorldTransformer/WorldTransformer.cpp src/Camera/Camera.cpp src/Drawer/Drawer.cpp)
set(SOURCE_FILES_PHONG src/main_phong.cpp src/Figure/Figure.cpp src/SolidParser/JsonParser.cpp src/WorldTransformer/WorldTransformer.cpp src/Camera/Camera.cpp src/Drawer/Drawer.cpp)
#add_executable(vcam  ${SOURCE_FILES})       
add_executable(vcam ${SOURCE_FILES})
add_executable(phong ${SOURCE_FILES_PHONG})
target_link_libraries (vcam  ${LIBS})
target_link_libraries (phong  ${LIBS})
