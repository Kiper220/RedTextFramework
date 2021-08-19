//
// Created by Гедерт Корней on 17.08.2021.
//

#ifndef CMAKE_INSTALL_CMAKE_ALLOCATOR_H
#define CMAKE_INSTALL_CMAKE_ALLOCATOR_H
#include <string.h>
#include <RTD/Memory/Memory.h>
//#define destroy std::destroy

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
                    Memory::Destroy((T*)&memory[size*sizeof(T)], (T*)(&memory[this->allocatedSize*sizeof(T)]));

                else if(size > this->allocatedSize)
                    new(&memory[this->allocatedSize*sizeof(T)]) T[size - this->allocatedSize];

                this->allocatedSize = size;
                return (T*)this->memory;
            }

            ~BasicStackAllocator(){
                Memory::Destroy((T*)memory, (T*)(&memory[allocatedSize*sizeof(T)]));
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

            class Iterator{
            public:
                friend BasicAllocator;

                Iterator operator++(int){
                    Iterator iterator(this->pointer, this->basicAllocator);
                    if(*this != basicAllocator.end())
                        pointer++;

                    return iterator;
                }
                Iterator& operator++(){
                    if(*this != basicAllocator.end())
                        pointer++;

                    return *this;
                }

                Iterator operator--(int){
                    Iterator iterator(this->pointer, this->basicAllocator);
                    if(*this != basicAllocator.begin())
                        pointer--;

                    return iterator;
                }
                Iterator& operator--(){
                    if(*this != basicAllocator.begin())
                        pointer--;

                    return *this;
                }

                Iterator& operator+=(size_t num){
                    pointer += num;
                    id += num;
                    return *this;
                }
                Iterator& operator-=(size_t num){
                    pointer -= num;
                    id -= num;
                    return *this;
                }
                Iterator operator+(size_t num){
                    Iterator tmp = *this;
                    tmp += num;
                    return tmp;
                }
                Iterator operator-(size_t num){
                    Iterator tmp = *this;
                    tmp -= num;
                    return tmp;
                }

                bool operator==(const Iterator iterator) const{
                    return this->pointer == iterator.pointer;
                }
                bool operator==(const Iterator& iterator) const{
                    return this->pointer == iterator.pointer;
                }
                bool operator==(T* pointer) const{
                    return this->pointer == pointer;
                }
                bool operator==(const T* pointer) const{
                    return this->pointer == pointer;
                }
                bool operator==(size_t id) const{
                    return this->id == id;
                }

                bool operator!=(const Iterator iterator) const{
                    return this->pointer != iterator.pointer;
                }
                bool operator!=(const Iterator& iterator) const{
                    return this->pointer != iterator.pointer;
                }
                bool operator!=(T* pointer) const{
                    return this->pointer != pointer;
                }
                bool operator!=(const T* pointer) const{
                    return this->pointer != pointer;
                }
                bool operator!=(size_t id) const{
                    return this->id != id;
                }

                bool operator<(const Iterator iterator) const{
                    return this->id < iterator.id;
                }
                bool operator<(const Iterator& iterator) const{
                    return this->id < iterator.id;
                }
                bool operator<(size_t id) const{
                    return this->id < id;
                }

                bool operator<=(const Iterator iterator) const{
                    return this->id <= iterator.id;
                }
                bool operator<=(const Iterator& iterator) const{
                    return this->id <= iterator.id;
                }
                bool operator<=(size_t id) const{
                    return this->id <= id;
                }

                bool operator>(const Iterator iterator) const{
                    return this->id < iterator.id;
                }
                bool operator>(const Iterator& iterator) const{
                    return this->id < iterator.id;
                }
                bool operator>(size_t id) const{
                    return this->id > id;
                }

                bool operator>=(const Iterator iterator) const{
                    return this->id <= iterator.id;
                }
                bool operator>=(const Iterator& iterator) const{
                    return this->id <= iterator.id;
                }
                bool operator>=(size_t id) const{
                    return this->id >= id;
                }

                size_t GetSize(){
                    return this->id;
                }

                T& operator*(){
                    return *this->pointer;
                }
                const T& operator*() const{
                    return *this->pointer;
                }

            protected:
                Iterator(BasicAllocator& basicAllocator): pointer((T*)nullptr), basicAllocator(basicAllocator) {}
                Iterator(const Iterator& iterator): pointer(iterator.pointer), id(iterator.id), basicAllocator(iterator.basicAllocator) {}
                Iterator(T* pointer, BasicAllocator& basicAllocator): pointer(pointer), basicAllocator(basicAllocator) {}

                Iterator& operator=(const Iterator& iterator){
                    this->pointer = iterator.pointer;
                    this->id = iterator.id;
                    return *this;
                }
                Iterator& SetPointer(T* pointer, size_t id){
                    this->pointer = pointer;
                    this->id = id;
                    return *this;
                }
                Iterator& SetPointer(const T* pointer, size_t id){
                    this->pointer = pointer;
                    this->id = id;
                    return *this;
                }

                inline Iterator& operator+=(const Iterator& iterator){
                    return *this += iterator.id;
                }
                inline Iterator& operator-=(const Iterator& iterator){
                    return *this -= iterator.id;
                }
                inline Iterator operator+(const Iterator& iterator){
                    return *this + iterator.id;
                }
                inline Iterator operator-(const Iterator& iterator){
                    return *this + iterator.id;
                }

            private:
                Iterator() = delete;

            private:
                T* pointer = (T*)nullptr;
                size_t id = 0;
                BasicAllocator& basicAllocator;

            };

            BasicAllocator() = default;

            Iterator& Allocate(sizeType size){
                if(this->endIterator < size){
                    if(this->pageSize < size * sizeof(T)){
                        size_t newSize = ((size * sizeof(T))/_size + 1) * _size;
                        char* tmp = (char*)malloc(newSize);
                        memset(tmp, 0, newSize);

                        memmove(tmp, this->memory, this->endIterator.GetSize() * sizeof(T));
                        free(this->memory);

                        this->memory = tmp;

                        this->beginIterator.SetPointer((T*)tmp, 0);
                        this->endIterator = this->beginIterator + this->endIterator;

                        this->pageSize = newSize;
                    }
                    new(&*this->endIterator) T[size - this->endIterator.GetSize()];
                    this->endIterator += size - this->endIterator.GetSize();
                }
                else if(this->endIterator > size){
                    if(size_t newSize = ((size * sizeof(T))/_size + 1) * _size; newSize < this->pageSize){
                        char* tmp = (char*)malloc(newSize);
                        memset(tmp, 0, newSize);

                        memmove(tmp, this->memory, size * sizeof(T));

                        Destroy(&*(this->beginIterator + size), &*this->endIterator);
                        free(this->memory);
                        this->memory = tmp;

                        this->beginIterator.SetPointer((T*)tmp, 0);
                        this->endIterator = this->beginIterator + size;

                        this->pageSize = newSize;
                    } else
                        Destroy(&*(this->beginIterator + size), &*this->endIterator);
                    this->endIterator += size - this->endIterator.GetSize();
                }
                return this->beginIterator;
            }

            Iterator Insert(const Iterator& iterator, T data){

            }
            Iterator Insert(const Iterator& iterator, const T& data){

            }

            Iterator Emplace(const Iterator& iterator, T&& data){
                
            }

            Iterator& begin(){
                return this->beginIterator;
            }
            Iterator& end(){
                return this->beginIterator;
            }

            const Iterator& cbegin() const{
                return this->beginIterator;
            }
            const Iterator& cend() const{
                return this->beginIterator;
            }

            ~BasicAllocator(){
                if(&*beginIterator){
                    Destroy(&*this->beginIterator, &*this->endIterator);
                    free(memory);
                }
            }

        private:
            BasicAllocator(const BasicAllocator& basicAllocator) = delete;

            Iterator beginIterator = (*this);
            Iterator endIterator = (*this);
            size_t pageSize = 0;
            char* memory = nullptr;
        };

    }
}
#endif //CMAKE_INSTALL_CMAKE_ALLOCATOR_H
