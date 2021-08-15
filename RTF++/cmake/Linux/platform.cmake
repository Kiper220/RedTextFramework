find_package(X11)

if(${X11_FOUND} AND ${X11_Xi_FOUND})
    message(STATUS "Window Server >>> X11")

else()
    message(FATAL_ERROR "X11 dev lib not found")
endif()

set(PLATFORM_LIBS ${X11_LIBRARIES} ${X11_Xi_LIB})
set(PLATFORM_INC ${X11_INCLUDE_DIR} ${X11_Xi_INCLUDE_PATH})