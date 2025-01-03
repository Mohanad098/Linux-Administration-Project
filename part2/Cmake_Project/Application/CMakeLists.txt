cmake_minimum_required(VERSION 3.10)

# Project Name
project(CryptoApp)

# Set the output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out/libs)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out/libs)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out)

# Specify binary directories for out-of-tree source directories
add_subdirectory(../Modules/caesar_cipher ${CMAKE_BINARY_DIR}/caesar_cipher_build)
add_subdirectory(../Modules/xor_cipher ${CMAKE_BINARY_DIR}/xor_cipher_build)

# Add the main application
add_executable(output app.c)

# Include directories for Caesar and XOR cipher headers
target_include_directories(output PRIVATE
    ../Modules/caesar_cipher/inc
    ../Modules/xor_cipher/inc
)

# Link the Caesar and XOR libraries with the application
target_link_libraries(output PRIVATE caesar_cipher xor_cipher)

