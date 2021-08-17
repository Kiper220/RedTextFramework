include(${CMAKE_CURRENT_LIST_DIR}/Types/Types.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/Math/Math.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/Strings/Strings.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/Exceptions/Exceptions.cmake)

set(RTF_RTD
        ${RTF_RTD_TYPES}
        ${RTF_RTD_MATH}
        ${RTF_RTD_STRINGS}
        ${RTF_RTD_EXCEPTIONS})