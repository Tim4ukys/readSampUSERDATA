cmake_minimum_required(VERSION 3.16)
project(readSampUSERDATA)

set(CMAKE_CXX_STANDARD 17)

add_executable(readSampUSERDATA main.cpp USERDATA.cpp)