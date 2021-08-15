cmake_minimum_required(VERSION 3.9.2)

#Корней, ты меня конечно прости, но мне понравились переменные в CMake
set(PROJECT_NAME RedTextApplication)
project(${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 17)

if(WIN32)
    set(dir ${PROJECT_SOURCE_DIR})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${dir}/bin")
endif()

set(Tests ON)

add_subdirectory(RTF++)

add_executable(${PROJECT_NAME} main.cpp)


target_link_libraries(${PROJECT_NAME} RTF_PP)
