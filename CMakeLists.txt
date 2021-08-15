cmake_minimum_required(VERSION 3.9.2)

#Korney, du vergib mir natürlich, aber ich mochte die Variablen in CMake
#Ich vergebe nicht

# TODO: Make a translation into all languages of the world

set(PROJECT_NAME RedTextApplication)
project(${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} main.cpp)

set(Tests ON)

add_subdirectory(RTF++)
target_link_libraries(${PROJECT_NAME} RTF_PP)
