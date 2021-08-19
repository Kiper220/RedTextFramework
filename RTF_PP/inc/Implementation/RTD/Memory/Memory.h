//
// Created by kiper220 on 23.07.2021.
//

#ifndef REDTEXTAPPLICATION_MEMORY_H
#define REDTEXTAPPLICATION_MEMORY_H
#include <atomic>
#include <cstdio>

namespace RTF{
    namespace Memory{

        template<typename T>
        class PointerType{
        public:
            PointerType(T* data = (T*)nullptr, size_t counter = 0, bool isLiteral = false): data(data), counter(counter), isLiteral(isLiteral){}
            PointerType(const PointerType& pointerType): data(pointerType.data), counter(pointerType.counter), isLiteral(pointerType.isLiteral){}
            PointerType& operator=(const PointerType& pointerType){
                this->data = pointerType.data;
                this->counter = pointerType.counter;
                this->isLiteral = pointerType.isLiteral;

                return *this;
            }
            bool operator==(const PointerType& pointerType) noexcept{
                return this->data == pointerType.data;
            }
            bool operator==(T* data) noexcept{
                return this->data == data;
            }
            bool operator!=(const PointerType& pointerType) noexcept{
                return this->data != pointerType.data;
            }
            bool operator!=(T* data) noexcept{
                return this->data != data;
            }


            T* data;
            std::atomic<size_t> counter;
            bool isLiteral;
        };
        template<typename T>
        struct IteratorTraits{
        public:
            typedef T   ValueType;
            typedef T*  ValuePointer;
            typedef T&  ValueReference;
        };
        template<typename T>
        struct IteratorTraits<T*>{
        public:
            typedef T   ValueType;
            typedef T*  ValuePointer;
            typedef T&  ValueReference;
        };
        template<typename T>
        struct IteratorTraits<const T*>{
        public:
            typedef T   ValueType;
            typedef T*  ValuePointer;
            typedef T&  ValueReference;
        };
        template<typename T>
        inline void Destroy(T* pointer){
            pointer->~T();
        }


        template<typename T>
        inline void Destroy(T begin, T end) {
            typedef typename IteratorTraits<T>::ValueType _Value_type;
            if constexpr (!std::is_trivially_destructible_v<_Value_type>){
                for(; begin != end; ++begin)
                    Destroy(begin);
            }
        }
    }
}

#endif //REDTEXTAPPLICATION_MEMORY_H
