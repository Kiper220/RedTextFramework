//
// Created by Гедерт Корней on 17.08.2021.
//

#ifndef CMAKE_INSTALL_CMAKE_ALLOCATOR_H
#define CMAKE_INSTALL_CMAKE_ALLOCATOR_H
#include <RTD/Memory/Memory.h>
#include <cstdlib>
#include <new>
//#define destroy std::destroy

namespace RTF {
    namespace Memory {

        template<typename T, size_t _size = 512>
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
        template<typename T, size_t _size = 512>
        class BasicAllocator{
        public:
            using sizeType = size_t;

            class Iterator{
            public:
                friend BasicAllocator;

                Iterator(const Iterator& iterator):
                        pointer(iterator.pointer),
                        id(iterator.id),
                        basicAllocator(iterator.basicAllocator) {}

                Iterator operator++(int){
                    Iterator iterator(this->pointer, this->id, this->basicAllocator);
                    if(*this != basicAllocator.end())
                        pointer++, id++;

                    return iterator;
                }
                Iterator& operator++(){
                    if(*this != basicAllocator.end())
                        pointer++, id++;

                    return *this;
                }

                Iterator operator--(int){
                    Iterator iterator(this->pointer, this->id, this->basicAllocator);
                    if(*this != basicAllocator.begin())
                        pointer--, id--;

                    return iterator;
                }
                Iterator& operator--(){
                    if(*this != basicAllocator.begin())
                        pointer--, id--;

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
                Iterator operator+(size_t num) const{
                    Iterator tmp = *this;
                    tmp += num;
                    return tmp;
                }
                Iterator operator-(size_t num) const{
                    Iterator tmp = *this;
                    tmp -= num;
                    return tmp;
                }

                inline Iterator& operator+=(const Iterator& iterator){
                    return *this += iterator.GetId();
                }
                inline Iterator& operator-=(const Iterator& iterator){
                    return *this -= iterator.GetId();
                }
                inline Iterator operator+(const Iterator& iterator) const{
                    return *this + iterator.GetId();
                }
                inline Iterator operator-(const Iterator& iterator) const{
                    return *this + iterator.GetId();
                }

                bool operator==(const Iterator& iterator) const{
                    return this->id == iterator.id;
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

                bool operator!=(const Iterator& iterator) const{
                    return this->id != iterator.id;
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

                bool operator<(const Iterator& iterator) const{
                    return this->id < iterator.id;
                }
                bool operator<(size_t id) const{
                    return this->id < id;
                }

                bool operator<=(const Iterator& iterator) const{
                    return this->id <= iterator.id;
                }
                bool operator<=(size_t id) const{
                    return this->id <= id;
                }

                bool operator>(const Iterator& iterator) const{
                    return this->id < iterator.id;
                }
                bool operator>(size_t id) const{
                    return this->id > id;
                }

                bool operator>=(const Iterator& iterator) const{
                    return this->id <= iterator.id;
                }
                bool operator>=(size_t id) const{
                    return this->id >= id;
                }

                size_t GetId() const{
                    return this->id;
                }
                Iterator& begin(){
                    return *this;
                }
                Iterator& end(){
                    return this->basicAllocator.endIterator;
                }
                const Iterator& cbegin(){
                    return *this;
                }
                const Iterator& cend(){
                    return this->basicAllocator.endIterator;
                }

                T& operator*(){
                    return *this->pointer;
                }
                const T& operator*() const{
                    return *this->pointer;
                }
                operator T*(){
                    return this->pointer;
                }
                T* GetPointer(){
                    return this->pointer;
                }
                const T* GetPointer() const{
                    return this->pointer;
                }

            protected:
                Iterator(BasicAllocator& basicAllocator):
                pointer((T*)nullptr),
                basicAllocator(basicAllocator) {}

                Iterator(T* pointer, size_t id, BasicAllocator& basicAllocator):
                pointer(pointer),
                id(id),
                basicAllocator(basicAllocator) {}

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

            private:
                Iterator() = delete;

            private:
                T* pointer = (T*)nullptr;
                size_t id = 0;
                BasicAllocator& basicAllocator;

            };

            BasicAllocator() = default;
            explicit BasicAllocator(size_t size){
                size_t newSize = ((size * sizeof(T))/_size + 1) * _size;
                char* tmp = (char*)malloc(newSize);
                MemSet(tmp, 0, newSize);

                if(this->memory != nullptr){
                    MemCopy<true>(tmp, this->memory, this->endIterator.id * sizeof(T));
                    free(this->memory);
                }

                this->memory = tmp;

                this->beginIterator.SetPointer((T*)tmp, 0);
                this->endIterator = this->beginIterator + this->endIterator;

                this->pageSize = newSize;

                new(this->endIterator.pointer) T[size - this->endIterator.id];
                this->endIterator += size - this->endIterator.id;
            }
            BasicAllocator(const T* pointer, size_t length) {
                if(length == 0)
                    return;

                this->pageSize = ((length * sizeof(T))/_size + 1) * _size;
                this->memory = (T*)malloc(this->pageSize);

                this->beginIterator.SetPointer((T*)this->memory, 0);
                this->endIterator = this->beginIterator + length;

                if constexpr(!std::is_class_v<T>){
                    Memory::MemCopy<true>(this->memory, pointer, this->endIterator.id * sizeof(T));
                    return;
                }
                else {
                    if constexpr(std::is_trivially_copy_constructible_v<T>)
                        for(Iterator &s: *this)
                            new(s.pointer) T(pointer[s.id]);
                    else if constexpr(std::is_trivially_constructible_v<T>)
                        for(Iterator &s: *this) {
                            new(s.pointer) T;
                            *s.pointer = pointer[s.id];
                        }
                    else
                        Memory::MemCopy<true>(this->memory, pointer, this->endIterator.id * sizeof(T));
                    return;
                }
            }
            BasicAllocator(const BasicAllocator& basicAllocator) {
                if(&basicAllocator == this)
                    return;
                if(basicAllocator.pageSize == 0)
                    return;
                this->pageSize = basicAllocator.pageSize;
                this->memory = (T*)malloc(basicAllocator.pageSize);

                this->beginIterator.SetPointer((T*)this->memory, 0);
                this->endIterator = this->beginIterator + basicAllocator.endIterator.id;

                if constexpr(!std::is_class_v<T>){
                    Memory::MemCopy<true>(this->memory, basicAllocator.memory, this->endIterator.id * sizeof(T));
                    return;
                }
                else {
                    if constexpr(std::is_trivially_copy_constructible_v<T>)
                        for(Iterator &s: *this)
                            new(s.pointer) T(basicAllocator.beginIterator.pointer[s.id]);
                    else if constexpr(std::is_trivially_constructible_v<T>)
                        for(Iterator &s: *this)
                            new(s.pointer) T;
                    else
                        Memory::MemCopy<true>(this->memory, basicAllocator.memory, this->endIterator.id * sizeof(T));
                    return;
                }
            }
            BasicAllocator& Set(const T* pointer, size_t length){
                if(this->pageSize <= length * sizeof(T)){
                    if(this->memory){
                        Destroy(&*this->beginIterator, &*this->endIterator);
                        free(memory);

                        this->memory = nullptr;
                        this->pageSize = 0;
                        this->beginIterator.pointer = (T*)nullptr;
                        this->endIterator.pointer = (T*)nullptr;
                    }

                    this->pageSize = ((length * sizeof(T))/_size + 1) * _size;
                    this->memory = (char*)malloc(this->pageSize);

                }else if(this->memory){
                    Destroy(this->beginIterator.pointer, this->endIterator.pointer);
                }
                this->beginIterator.SetPointer((T*)this->memory, 0);
                this->endIterator = this->beginIterator + length;

                if constexpr(!std::is_class_v<T>){
                    Memory::MemCopy<true>(this->memory, pointer, this->endIterator.id * sizeof(T));
                    return *this;
                }
                else {
                    this->beginIterator.SetPointer((T*)this->memory, 0);
                    this->endIterator = this->beginIterator + length;

                    if constexpr(std::is_trivially_copy_constructible_v<T>)
                        for(Iterator &s: *this)
                            new(s.pointer) T(pointer[s.id]);
                    else if constexpr(std::is_trivially_constructible_v<T>)
                        for(Iterator &s: *this)
                            new(s.pointer) T;
                    else
                        Memory::MemCopy<true>(this->memory, pointer, this->endIterator.id * sizeof(T));
                }
                return *this;
            }
            BasicAllocator& operator=(BasicAllocator&& basicAllocator) noexcept {
                this->pageSize = basicAllocator.pageSize;
                this->memory = basicAllocator.memory;
                this->beginIterator.pointer = (T*)this->memory;
                this->endIterator = this->beginIterator + basicAllocator.endIterator.id;

                basicAllocator.memory = nullptr;
                basicAllocator.pageSize = 0;
                basicAllocator.beginIterator.pointer = (T*)nullptr;
                basicAllocator.endIterator.pointer = (T*)nullptr;

                return *this;
            }
            BasicAllocator& operator=(const BasicAllocator& basicAllocator) {
                if(&basicAllocator == this)
                    return *this;
                if(this->memory != nullptr){
                    Destroy(&*this->beginIterator, &*this->endIterator);
                    free(this->memory);

                    this->memory = nullptr;
                    this->pageSize = 0;
                    this->beginIterator.pointer = (T*)nullptr;
                    this->endIterator.pointer = (T*)nullptr;
                }

                if(basicAllocator.pageSize == 0)
                    return *this;
                this->pageSize = basicAllocator.pageSize;
                this->memory = (char*)malloc(basicAllocator.pageSize);

                this->beginIterator.SetPointer((T*)this->memory, 0);
                this->endIterator = this->beginIterator + basicAllocator.endIterator.id;


                if constexpr(!std::is_class_v<T>){
                    Memory::MemCopy<true>(this->memory, basicAllocator.memory, this->endIterator.id * sizeof(T));
                    return *this;
                }
                else {
                    if constexpr(!std::is_trivially_copy_constructible_v<T>)
                        for(Iterator i = this->begin(); i != this->endIterator; i++)
                            new(i.pointer) T(basicAllocator.beginIterator.pointer[i.id]);
                    else if constexpr(!std::is_trivially_constructible_v<T>)
                    for(Iterator &s: *this)
                        new(s.pointer) T;
                    else
                        Memory::MemCopy<true>(this->memory, basicAllocator.memory, this->endIterator.id * sizeof(T));
                    return *this;
                }
            }

            Iterator& Allocate(sizeType size){
                if(this->endIterator < size){
                    if(this->pageSize < size * sizeof(T)){
                        size_t newSize = ((size * sizeof(T))/_size + 1) * _size;
                        char* tmp = (char*)malloc(newSize);
                        MemSet(tmp, 0, newSize);

                        if(this->memory != nullptr){
                            MemCopy<true>(tmp, this->memory, this->endIterator.id * sizeof(T));
                            free(this->memory);
                        }

                        this->memory = tmp;

                        this->beginIterator.SetPointer((T*)tmp, 0);
                        this->endIterator = this->beginIterator + this->endIterator;

                        this->pageSize = newSize;
                    }
                    new(this->endIterator.pointer) T[size - this->endIterator.id];
                    this->endIterator += size - this->endIterator.id;
                }
                else if(this->endIterator > size){
                    size_t newSize = ((size * sizeof(T))/_size + 1) * _size;
                    if(newSize < this->pageSize){
                        char* tmp = (char*)malloc(newSize);
                        MemSet(tmp, 0, newSize);

                        MemCopy<true>(tmp, this->memory, size * sizeof(T));

                        Destroy((this->beginIterator + size).pointer, this->endIterator.pointer);
                        free(this->memory);
                        this->memory = tmp;

                        this->beginIterator.SetPointer((T*)tmp, 0);
                        this->endIterator = this->beginIterator + size;

                        this->pageSize = newSize;
                    } else{
                        Destroy((this->beginIterator + size).pointer, this->endIterator.pointer);
                        MemSet((this->beginIterator + size).pointer, 0, (this->endIterator.id - size) * sizeof(T));
                    }
                    this->endIterator += size - this->endIterator.id;
                }
                return this->beginIterator;
            }

            /*Iterator Insert(const Iterator& iterator, T data){
                if(this->pageSize < (this->endIterator * sizeof(T)).id){
                    size_t newSize = ((this->endIterator.id * sizeof(T))/_size + 1) * _size;
                    char* tmp = (char*)malloc(newSize);
                    memset(tmp, 0, newSize);

                    memmove(tmp, this->memory, this->iterator.id * sizeof(T));
                    memmove(tmp + (this->iterator.id + 1) * sizeof(T),
                            this->memory  + this->iterator.id,
                            (this->endIterator.id - iterator.id - 1) * sizeof(T));

                    new(tmp + (this->iterator.id)) T(data);
                    free(this->memory);

                    this->memory = tmp;
                    this->beginIterator = this->memory;
                    this->endIterator = this->beginIterator + this->endIterator + 1;

                }
                else{
                    memmove(this->beginIterator.pointer + (this->iterator.id + 1) * sizeof(T),
                            this->beginIterator.pointer + (this->iterator.id) * sizeof(T),
                            this->endIterator.id * sizeof(T));

                    new(this->beginIterator.pointer + (this->iterator.id)) T(data);

                    this->endIterator += 1;
                }

                return Iterator(this->beginIterator.pointer + this->iterator.id, this->iterator.id, *this);
            }*/

            Iterator Insert(const Iterator& iterator, const T& data){
                if(this->pageSize < this->endIterator.id * sizeof(T)){
                    size_t newSize = ((this->endIterator.id * sizeof(T))/_size + 1) * _size;
                    char* tmp = (char*)malloc(newSize);
                    MemSet(tmp, 0, newSize);

                    MemCopy<true>(tmp, this->memory, iterator.id * sizeof(T));
                    MemCopy<true>(tmp + (iterator.id + 1) * sizeof(T),
                            this->memory  + iterator.id,
                            (this->endIterator.id - iterator.id - 1) * sizeof(T));

                    if constexpr(std::is_trivially_copy_constructible_v<T>){
                        new(iterator.pointer) T(data);
                    }
                    else{
                        new(iterator.pointer) T;
                    }
                    free(this->memory);

                    this->memory = tmp;
                    this->beginIterator.pointer = (T*)this->memory;
                    this->endIterator = this->beginIterator + this->endIterator + 1;

                }
                else{
                    char* data = (char*)iterator.pointer;
                    size_t size = (this->endIterator.id - iterator.id) * sizeof(T);
                    MemCopy<false>((char*)&iterator.pointer[1], (char*)iterator.pointer, (this->endIterator.id - iterator.id) * sizeof(T));
                    MemSet(iterator.pointer, 0, sizeof(T));


                    if constexpr(std::is_trivially_copy_constructible_v<T>){
                        new(iterator.pointer) T(data);
                    }
                    else{
                        new(iterator.pointer) T;
                    }

                    this->endIterator += 1;
                }

                return Iterator(this->beginIterator.pointer + iterator.id, iterator.id, *this);
            }
            Iterator Insert(const Iterator& iterator){
                if(this->pageSize < this->endIterator.id * sizeof(T)){
                    size_t newSize = ((this->endIterator.id * sizeof(T))/_size + 1) * _size;
                    char* tmp = (char*)malloc(newSize);
                    MemSet(tmp, 0, newSize);

                    MemCopy<true>(tmp, this->memory, iterator.id * sizeof(T));
                    MemCopy<true>(tmp + (iterator.id + 1) * sizeof(T),
                            this->memory  + iterator.id,
                            (this->endIterator.id - iterator.id - 1) * sizeof(T));

                    new(tmp + (iterator.id)) T();
                    free(this->memory);

                    this->memory = tmp;
                    this->beginIterator.pointer = (T*)this->memory;
                    this->endIterator = this->beginIterator + this->endIterator + 1;

                }
                else{
                    MemCopy<false>(&iterator.pointer[1], iterator.pointer, (this->endIterator.id - iterator.id) * sizeof(T));
                    MemSet(iterator.pointer, 0, sizeof(T));

                    new(iterator.pointer) T();

                    this->endIterator += 1;
                }

                return Iterator(this->beginIterator.pointer + iterator.id, iterator.id, *this);
            }

            Iterator Emplace(const Iterator& iterator, T&& data){
                if(this->pageSize < this->endIterator.id * sizeof(T)){
                    size_t newSize = ((this->endIterator.id * sizeof(T))/_size + 1) * _size;
                    char* tmp = (char*)malloc(newSize);
                    MemSet(tmp, 0, newSize);

                    MemCopy(tmp, this->memory, iterator.id * sizeof(T));
                    MemCopy(tmp + (this->iterator.id + 1) * sizeof(T),
                            this->memory  + iterator.id,
                            (this->endIterator.id - iterator.id - 1) * sizeof(T));

                    new(tmp + (iterator.id)) T(data);
                    free(this->memory);

                    this->memory = tmp;
                    this->beginIterator = this->memory;
                    this->endIterator = this->beginIterator + this->endIterator + 1;

                }
                else{
                    MemCopy(this->beginIterator.pointer + (this->iterator.id + 1) * sizeof(T),
                            this->beginIterator.pointer + (this->iterator.id) * sizeof(T),
                            this->endIterator.id * sizeof(T));

                    new(this->beginIterator.pointer + (this->iterator.id)) T(data);

                    this->endIterator += 1;
                }

                return Iterator(this->beginIterator.pointer + this->iterator.id, this->iterator.id, *this);
            }

            Iterator& begin(){
                return this->beginIterator;
            }
            Iterator& end(){
                return this->endIterator;
            }

            char& operator[](size_t i){
                return this->memory[i];
            }
            const char& operator[](size_t i) const{
                return this->memory[i];
            }

            const Iterator& cbegin() const{
                return this->beginIterator;
            }
            const Iterator& cend() const{
                return this->endIterator;
            }
            void ClearWithoutDestroy(){
                if(this->memory){
                    free(memory);

                    this->memory = nullptr;
                    this->pageSize = 0;
                    this->beginIterator.pointer = (T*)nullptr;
                    this->endIterator.pointer = (T*)nullptr;
                }
            }

            ~BasicAllocator(){
                if(this->memory){
                    Destroy(&*this->beginIterator, &*this->endIterator);
                    free(memory);

                    this->memory = nullptr;
                    this->pageSize = 0;
                    this->beginIterator.pointer = (T*)nullptr;
                    this->endIterator.pointer = (T*)nullptr;
                }
            }

        private:

            Iterator beginIterator = (*this);
            Iterator endIterator = (*this);
            size_t pageSize = 0;
            char* memory = nullptr;
        };
    }

#ifdef TESTS_ON
bool TEST(RTD, Memory, BasicAllocator)();
#endif
}
#endif //CMAKE_INSTALL_CMAKE_ALLOCATOR_H
