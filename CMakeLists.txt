cmake_minimum_required(VERSION 3.19)

# Executable name/version
project(des VERSION 0.1)

# Set source and include directory variables
set(PROJECT_SOURCE_DIR src)
set(PROJECT_INCLUDE_DIR inc)

# Find all source files
file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/*.c)

# Set up source and includes for compilation
add_executable(des ${SOURCES})
target_include_directories(des PUBLIC ${PROJECT_INCLUDE_DIR})
