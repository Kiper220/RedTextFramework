
message("-------------- Configuring Dependencies --------------")

if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()

if(UNIX AND APPLE)
    set(MACOS TRUE)
endif()

if(LINUX)
    message(STATUS "Platform >>> Linux")
    include(${CMAKE_CURRENT_LIST_DIR}/Linux/platform.cmake)
elseif(WIN32)
    include(${CMAKE_CURRENT_LIST_DIR}/Windows/platform.cmake)
    message(STATUS "Platform >>> Windows")

elseif(MACOS)
    message(STATUS "Platform >>> MacOS")

else()
    message(FATAL_ERROR "THIS PLATFORM DON'T SUPPORTED")

endif()

if(Tests)
    message(STATUS "Tests >>> ON")
    add_definitions("-DTESTS_ON")
endif()

message("-------------- Completing The Configuration --------------")