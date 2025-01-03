# Specify the minimum version for CMake
cmake_minimum_required(VERSION 3.10)

# Set the project name
project(XORCipher)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/inc)

# Add the library (shared/dynamic)
add_library(xor_cipher SHARED src/xor_encrypt.c src/xor_decrypt.c)

# Specify where to put the object files
set_target_properties(xor_cipher PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out/libs
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out/libs
)

