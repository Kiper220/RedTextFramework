//
// Created by kiper220 on 24.08.2021.
//

#ifndef CMAKE_INSTALL_CMAKE_IALLOCATOR_H
#define CMAKE_INSTALL_CMAKE_IALLOCATOR_H

namespace RTF {
    namespace Memory {

        template<typename T, int _size = 512>
        class BasicStackAllocator;

        template<typename T, int _size = 512>
        class BasicAllocator;
    }
}

#endif //CMAKE_INSTALL_CMAKE_IALLOCATOR_H
