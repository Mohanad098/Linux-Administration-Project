# Specify the minimum version for CMake
cmake_minimum_required(VERSION 3.10)

# Set the project name
project(CaesarCipher)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/inc)

# Add the library (static)
add_library(caesar_cipher STATIC src/caesar_encrypt.c src/caesar_decrypt.c)

# Specify where to put the object files
set_target_properties(caesar_cipher PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out/libs
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out/libs
)

