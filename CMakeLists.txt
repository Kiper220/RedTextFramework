cmake_minimum_required(VERSION 3.9.2)

#Корней, ты меня конечно прости, но мне понравились переменные в CMake
set(PROJECT_NAME RedTextApplication)
project(${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} main.cpp)

set(Tests ON)

add_subdirectory(RTF++)
target_link_libraries(${PROJECT_NAME} RTF_PP)