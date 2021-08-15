find_package(X11)

if(${X11_FOUND})
    message(STATUS "Window Server >>> X11")

else()
    message(FATAL_ERROR "X11 dev lib not found")
endif()

set(PLATFORM_LIBS ${X11_LIBRARIES})
set(PLATFORM_INC ${X11_INCLUDE_DIR})