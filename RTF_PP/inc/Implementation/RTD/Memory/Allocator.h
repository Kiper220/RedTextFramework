//
// Created by Гедерт Корней on 17.08.2021.
//

#ifndef CMAKE_INSTALL_CMAKE_ALLOCATOR_H
#define CMAKE_INSTALL_CMAKE_ALLOCATOR_H
#include <string.h>
#ifdef WIN32
#include <xmemory>
#elif linux
#include <bits/stl_construct.h>
#endif
#define destroy std::destroy

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
                    destroy((T*)&memory[size*sizeof(T)], (T*)(&memory[this->allocatedSize*sizeof(T)]));

                else if(size > this->allocatedSize)
                    new(&memory[this->allocatedSize*sizeof(T)]) T[size - this->allocatedSize];

                this->allocatedSize = size;
                return (T*)this->memory;
            }

            ~BasicStackAllocator(){
                destroy((T*)memory, (T*)(&memory[allocatedSize*sizeof(T)]));
            }

        private:
            BasicStackAllocator(const BasicStackAllocator& basicStackAllocator);

            size_t allocatedSize = 0;
            char memory[_size];
        };
        template<typename T, int _size = 512>
        class BasicAllocator{
        public:
            using sizeType = size_t;

            BasicAllocator() = default;

            T* Allocate(sizeType size){
                size_t firstPosition = this->allocatedSize / sizeof(T);
                if(firstPosition < size){
                    if(this->pageSize < size * sizeof(T)){
                        this->pageSize = ((size * sizeof(T)) / _size)*_size + _size;
                        char* tmp = new char[pageSize];
                        memset(tmp, 0, pageSize);

                        if(this->memory != nullptr){
                            memmove(tmp, memory, allocatedSize);
                            delete[] memory;
                        }
                        this->memory = tmp;
                    }

                    new(&memory[this->allocatedSize]) T[size - firstPosition];
                }
                else {
                    destroy(&((T*)memory)[size], &((T*)memory)[firstPosition]);

                    memset(&((T*)memory)[size], 0, (firstPosition - size) * sizeof(T));

                    allocatedSize = size * sizeof(T);

                    if(this->pageSize > ((size * sizeof(T)) / _size)*_size + _size){
                        this->pageSize = ((size * sizeof(T)) / _size)*_size + _size;
                        char* tmp = new char[pageSize];
                        memset(tmp, 0, pageSize);

                        if(this->memory != nullptr){
                            memmove(tmp, memory, allocatedSize);
                            delete[] memory;
                        }
                        this->memory = tmp;
                    }

                }
                allocatedSize = size * sizeof(T);
                return (T*)this->memory;
            }

            ~BasicAllocator(){
                destroy(((T*)memory), &((T*)memory)[this->allocatedSize / sizeof(T)]);
                delete[] memory;
            }

        private:
            BasicAllocator(const BasicAllocator& basicAllocator);

            size_t allocatedSize = 0;
            size_t pageSize = 0;
            char* memory = nullptr;
        };

    }
}
#endif //CMAKE_INSTALL_CMAKE_ALLOCATOR_H
