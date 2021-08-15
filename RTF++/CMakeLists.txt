cmake_minimum_required(VERSION 3.9.2)
project(RedTextFramework)

set(CMAKE_CXX_STANDARD 17)

include(src/src.cmake)
include(cmake/main.cmake)

if(WIN32)
    add_library(RTF_PP STATIC ${RTF_SRC})
else()
    add_library(RTF_PP STATIC ${RTF_SRC})
endif()

target_link_libraries(RTF_PP ${PLATFORM_LIBS})
target_include_directories(RTF_PP PUBLIC inc/Interface inc/Implementation inc/Tests ${PLATFORM_INC})