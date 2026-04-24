

cmake_minimum_required(VERSION 3.10)
project(ComplexNumber)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall -Wextra -Wpedantic")

# Create the executable
add_executable(code main.cpp complex.hpp)

# Include current directory for header files
target_include_directories(code PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

