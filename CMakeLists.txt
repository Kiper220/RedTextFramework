cmake_minimum_required(VERSION 3.9.2)
project(RedTextApplication)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(RTF++)

add_executable(RedTextApplication main.cpp)
target_link_libraries(RedTextApplication RTF_PP)