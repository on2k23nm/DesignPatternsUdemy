# cmake -DCMAKE_BUILD_TYPE=Debug -S ../ -B ./

cmake_minimum_required(VERSION 3.0)

project(DesignPatternsUdemy)

# Find the latest GCC compiler on the system
find_program(GCC_COMPILER gcc)
message(STATUS "Using GCC compiler: ${CMAKE_C_COMPILER}")

if(GCC_COMPILER)
    set(CMAKE_C_COMPILER ${GCC_COMPILER})
else()
    message(FATAL_ERROR "GCC compiler not found. Make sure it's installed and in your system's PATH.")
endif()

# If you want to set flags for a specific build type (e.g., Debug):
# Invoke cmake -DCMAKE_BUILD_TYPE=Debug -S ../ -B ./, then when you do make, it will build debugabble exe's
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0 -g")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g")

add_subdirectory(Sec02)
add_subdirectory(Sec03)
add_subdirectory(Misc)
