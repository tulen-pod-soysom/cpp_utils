cmake_minimum_required(VERSION 3.5.0)
project(test VERSION 0.1.0 LANGUAGES C CXX)
set(CXX_STANDARD 21)

include_directories(~/workspace/cpp_utils)

add_executable(test test10.cpp)

