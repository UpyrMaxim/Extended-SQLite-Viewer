cmake_minimum_required(VERSION 3.12)
project(parser)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
find_package(OpenMP REQUIRED)

add_executable(parser main.cpp Database.cpp Database.h )

target_compile_options(parser PRIVATE -Wall ${OpenMP_CXX_FLAGS})
target_link_libraries(parser PRIVATE ${OpenMP_CXX_FLAGS})
