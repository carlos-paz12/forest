cmake_minimum_required(VERSION 3.22.1)
project(forest VERSION 1.0 DESCRIPTION "Implementation of the AVL and Black-Red trees." LANGUAGES CXX)

# Set the C++ language standard.
#
# Using C++17.
set(CMAKE_CXX_STANDARD 17)
# Require the compiler to support exactly this standard.
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Flag to set the binaries output directory.
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Flag to generate compile_commands.json (Useful for clangd).
# set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Adds the includes directory.
include_directories(include)
include_directories(lib)

# Recursively searches for all .cpp files in src/ and subdirectories.
file(GLOB_RECURSE SOURCES
    src/*.cpp
)

# Create the executable called 'forest' using the source files found.
add_executable(forest ${SOURCES})

# Adds the include directories to the 'forest' target.
target_include_directories(forest PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/lib
)
# Set compilation flags.
target_compile_options(forest PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -O2
)