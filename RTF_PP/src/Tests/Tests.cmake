include(${CMAKE_CURRENT_LIST_DIR}/RTD/RTD.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/Platform/Platform.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/Application/Application.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/DataCollect/DataCollect.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/Widget/Widget.cmake)

if(Tests)
    set(RTF_TESTS
            ${CMAKE_CURRENT_LIST_DIR}/Tests.cpp
            ${RTF_TESTS_RTD}
            ${RTF_TESTS_APPLICATION}
            ${RTF_TESTS_DATACOLLECT}
            ${RTF_TESTS_PLATFORM}
            ${RTF_TESTS_WIDGET})
else()
    set(RTF_TESTS ${CMAKE_CURRENT_LIST_DIR}/Tests.cpp)
endif()

#Containers::Pair<bool,Containers::Pair<Module,UnderModule>> RunAllTest();