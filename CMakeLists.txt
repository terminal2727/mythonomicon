# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(Mythonomicon VERSION 0.0.1)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set sources (sure hope HEADER_DIRS is right XP)
set(SOURCES
    ${CMAKE_SOURCE_DIR}/src/main.cpp
    ${CMAKE_SOURCE_DIR}/src/mythos_engine/mythos_engine.cpp
    ${CMAKE_SOURCE_DIR}/src/mythos_engine/rendering/rendering_pipeline.cpp
    ${CMAKE_SOURCE_DIR}/src/mythos_engine/rendering/display_management/display_manager.cpp
    ${CMAKE_SOURCE_DIR}/src/utils/type_registry/type_registry.cpp
)

file(GLOB_RECURSE HEADER_DIRS "src/**")

# Specify the source files
add_executable(Mythonomicon ${SOURCES} ${HEADERS})

# Includes
target_include_directories(Mythonomicon 
    PRIVATE
        ${CMAKE_SOURCE_DIR}/src/mythos_engine
        ${CMAKE_SOURCE_DIR}/src/mythos_engine/rendering
        ${CMAKE_SOURCE_DIR}/src/mythos_engine/rendering/display_management
        ${CMAKE_SOURCE_DIR}/src/utils/type_registry
)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Use vcpkg to find GLEW and GLFW
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)

# Include directories
include_directories(${GLEW_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS})

# Link libraries
target_link_libraries(Mythonomicon OpenGL::GL ${GLEW_LIBRARIES} glfw)