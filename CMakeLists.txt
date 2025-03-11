
cmake_minimum_required(VERSION 3.10)
project(hemlock-argparser VERSION 0.2.1 LANGUAGES C)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "$<1:${CMAKE_BINARY_DIR}/bin>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "$<1:${CMAKE_BINARY_DIR}/lib>")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "$<1:${CMAKE_BINARY_DIR}/lib>")

find_library(MATH_LIBRARY m)

add_subdirectory("./src")

# end of file
