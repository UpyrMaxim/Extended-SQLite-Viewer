cmake_minimum_required(VERSION 3.10.2)
project(parser)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
find_package(OpenMP REQUIRED)

add_executable(parser main.cpp Database.cpp Database.h FreeBlock_parser.cpp FreeBlock_parser.h)
add_library(parserlib SHARED Database.cpp Database.h FreeBlock_parser.cpp FreeBlock_parser.h)
target_compile_options(parser PRIVATE -Wall ${OpenMP_CXX_FLAGS})
target_link_libraries(parser PRIVATE ${OpenMP_CXX_FLAGS})
