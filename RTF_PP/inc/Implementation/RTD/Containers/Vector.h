//
// Created by kiper220 on 24.08.2021.
//
#include <RTD/Memory/Allocator.h>

#ifndef CMAKE_INSTALL_CMAKE_VECTOR_H
#define CMAKE_INSTALL_CMAKE_VECTOR_H

namespace RTF{
    namespace Containers{
        template<typename T, class Alloc = Memory::BasicAllocator<T>>
        class Vector{
        public:
            Vector() = default;
            Vector(const Vector& vector): allocator(vector.allocator) {}

            Vector& operator=(const Vector& vector){
                this->allocator = vector.allocator;
                return *this;
            }
        private:
            Alloc allocator;
        };
    }
}
#endif //CMAKE_INSTALL_CMAKE_VECTOR_H
