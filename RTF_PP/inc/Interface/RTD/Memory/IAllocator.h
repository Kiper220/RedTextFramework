//
// Created by kiper220 on 24.08.2021.
//

#ifndef CMAKE_INSTALL_CMAKE_IALLOCATOR_H
#define CMAKE_INSTALL_CMAKE_IALLOCATOR_H
#include <cstdio>

namespace RTF {
    namespace Memory {

        template<typename T, size_t _size>
        class BasicStackAllocator;

        template<typename T, size_t _size>
        class BasicAllocator;
    }
}

#endif //CMAKE_INSTALL_CMAKE_IALLOCATOR_H
