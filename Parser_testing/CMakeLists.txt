cmake_minimum_required(VERSION 3.12)
project(Parser_testing)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
find_package(OpenMP REQUIRED)
find_library(LIB libparserlib.so HINTS ../parser/cmake-build-debug/)
include_directories(../parser/)
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})




add_executable(Parser_testing main.cpp Database.h Database.cpp FreeBlock_parser.h FreeBlock_parser.cpp)

target_link_libraries(Parser_testing PUBLIC gtest gtest_main ${LIB})