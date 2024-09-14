# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(Mythonomicon VERSION 0.0.1)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Specify the source files
add_executable(MyOpenGLApp src/main.cpp)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Use vcpkg to find GLEW and GLFW
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)

# Include directories
include_directories(${GLEW_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS})

# Link libraries
target_link_libraries(MyOpenGLApp OpenGL::GL ${GLEW_LIBRARIES} glfw)