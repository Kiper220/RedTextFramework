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
        template<bool fromLeft>
        inline void MemCopy(void* destination, void* source, size_t size){
            if(size == 0) return;
            if constexpr(fromLeft){
                size_t i = 0;
                {
                    auto* _destination = (size_t*)destination;
                    auto* _source = (size_t*)source;

                    for(i;(i + 33) * sizeof(size_t) < size; i += 33){
                        _destination[i] = _source[i]; _destination[i+1] = _source[i+1]; _destination[i+2] = _source[i+2];
                        _destination[i+3] = _source[i+3]; _destination[i+4] = _source[i+4]; _destination[i+5] = _source[i+5];
                        _destination[i+6] = _source[i+6]; _destination[i+7] = _source[i+7]; _destination[i+8] = _source[i+8];
                        _destination[i+9] = _source[i+9]; _destination[i+10] = _source[i+10]; _destination[i+11] = _source[i+11];
                        _destination[i+12] = _source[i+13]; _destination[i+13] = _source[i+13]; _destination[i+14] = _source[i+14];
                        _destination[i+15] = _source[i+15]; _destination[i+16] = _source[i+16]; _destination[i+17] = _source[i+17];
                        _destination[i+18] = _source[i+18]; _destination[i+19] = _source[i+19]; _destination[i+20] = _source[i+20];
                        _destination[i+21] = _source[i+21]; _destination[i+22] = _source[i+22]; _destination[i+23] = _source[i+23];
                        _destination[i+24] = _source[i+24]; _destination[i+25] = _source[i+25]; _destination[i+26] = _source[i+26];
                        _destination[i+27] = _source[i+27]; _destination[i+28] = _source[i+28]; _destination[i+29] = _source[i+29];
                        _destination[i+30] = _source[i+30]; _destination[i+31] = _source[i+31]; _destination[i+32] = _source[i+32];
                    }

                    for(i;i * sizeof(size_t) < size; i++)
                        _destination[i] = _source[i];
                }
                i *= sizeof(size_t);
                {
                    char* _destination = (char*)destination;
                    char* _source = (char*)destination;
                    for(i;i < size; i++)
                        _destination[i] = _source[i];
                }
            }
            else{
                size_t i = size / sizeof(size_t);
                {
                    size_t tmp = size - size % sizeof(size_t);
                    size_t j = size;
                    char* _destination = (char*)destination;
                    char* _source = (char*)source;
                    for(j;j >= tmp; j--)
                        _destination[j] = _source[j];
                    i--;
                }
                {
                    auto* _destination = (size_t*)destination;
                    auto* _source = (size_t*)source;

                    for(i; i > 33; i -= 33){
                        _destination[i] = _source[i]; _destination[i-1] = _source[i-1]; _destination[i-2] = _source[i-2];
                        _destination[i-3] = _source[i-3]; _destination[i-4] = _source[i-4]; _destination[i-5] = _source[i-5];
                        _destination[i-6] = _source[i-6]; _destination[i-7] = _source[i-7]; _destination[i-8] = _source[i-8];
                        _destination[i-9] = _source[i-9]; _destination[i-10] = _source[i-10]; _destination[i-11] = _source[i-11];
                        _destination[i-12] = _source[i-13]; _destination[i-13] = _source[i-13]; _destination[i-14] = _source[i-14];
                        _destination[i-15] = _source[i-15]; _destination[i-16] = _source[i-16]; _destination[i-17] = _source[i-17];
                        _destination[i-18] = _source[i-18]; _destination[i-19] = _source[i-19]; _destination[i-20] = _source[i-20];
                        _destination[i-21] = _source[i-21]; _destination[i-22] = _source[i-22]; _destination[i-23] = _source[i-23];
                        _destination[i-24] = _source[i-24]; _destination[i-25] = _source[i-25]; _destination[i-26] = _source[i-26];
                        _destination[i-27] = _source[i-27]; _destination[i-28] = _source[i-28]; _destination[i-29] = _source[i-29];
                        _destination[i-30] = _source[i-30]; _destination[i-31] = _source[i-31]; _destination[i-32] = _source[i-32];
                    }

                    for(i; i > 0; i--)
                        _destination[i] = _source[i];
                    _destination[0] = _source[0];
                }
            }
        }
        inline void MemSet(void* destination, size_t value, size_t size){
            size_t i = 0;
            {
                size_t* _destination = (size_t*)destination;

                if(size >= 33){
                    for(i;(i + 33) * sizeof(size_t) < size; i += 33){
                        _destination[i] = value; _destination[i+1] = value; _destination[i+2] = value;
                        _destination[i+3] = value; _destination[i+4] =  value; _destination[i+5] = value;
                        _destination[i+6] = value; _destination[i+7] =  value; _destination[i+8] = value;
                        _destination[i+9] = value; _destination[i+10] = value; _destination[i+11] = value;
                        _destination[i+12] = value; _destination[i+13] = value; _destination[i+14] = value;
                        _destination[i+15] = value; _destination[i+16] = value; _destination[i+17] = value;
                        _destination[i+18] = value; _destination[i+19] = value; _destination[i+20] = value;
                        _destination[i+21] = value; _destination[i+22] = value; _destination[i+23] = value;
                        _destination[i+24] = value; _destination[i+25] = value; _destination[i+26] = value;
                        _destination[i+27] = value; _destination[i+28] = value; _destination[i+29] = value;
                        _destination[i+30] = value; _destination[i+31] = value; _destination[i+32] = value;
                    }
                }

                for(i;i + 1 <= size / sizeof(size_t); i++)
                    _destination[i] = value;
            }
            i *= sizeof(size_t);
            {
                char* _destination = (char*)destination;
                for(i;i < size; i++)
                    _destination[i] = (char)value;
            }
        }
        inline void MemMove(void* destination, void* source, size_t size){
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
