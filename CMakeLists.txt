cmake_minimum_required(VERSION 3.9.2)

#Korney, du vergib mir natürlich, aber ich mochte die Variablen in CMake
#Ich vergebe nicht

# TODO: Make a translation into all languages of the world

set(PROJECT_NAME RedTextApplication)
project(${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 17)

set(dir ${PROJECT_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${dir}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${dir}/bin")

set(Tests ON)

add_subdirectory(RTF_PP)


add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} RTF_PP)
