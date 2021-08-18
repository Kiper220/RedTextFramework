//
// Created by Гедерт Корней on 17.08.2021.
//

#ifndef CMAKE_INSTALL_CMAKE_ALLOCATOR_H
#define CMAKE_INSTALL_CMAKE_ALLOCATOR_H
#include <xmemory>

namespace RTF {
    namespace Memory {

        template<typename T, int _size = 512>
        class BasicStackAllocator{
        public:
            using sizeType = size_t;

            BasicStackAllocator() = default;

            T* Allocate(sizeType size){
                if(!size)
                    return (T*)(this->memory);
                if(size * sizeof(T) > 512)
                    throw 123;

                if(size < this->allocatedSize)
                    std::destroy((T*)&memory[size*sizeof(T)], (T*)(&memory[this->allocatedSize*sizeof(T)]));
                else if(size > this->allocatedSize)
                    new(&memory[this->allocatedSize*sizeof(T)]) T[size - this->allocatedSize];

                this->allocatedSize = size;
                return (T*)this->memory;
            }

            ~BasicStackAllocator(){
                std::destroy((T*)memory, (T*)(&memory[allocatedSize*sizeof(T)]));
            }

        private:
            BasicStackAllocator(const BasicStackAllocator& basicStackAllocator);

            size_t allocatedSize = 0;
            char memory[_size];
        };

    }
}
#endif //CMAKE_INSTALL_CMAKE_ALLOCATOR_H
