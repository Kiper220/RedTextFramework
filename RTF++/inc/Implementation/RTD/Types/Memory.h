//
// Created by kiper220 on 23.07.2021.
//

#ifndef REDTEXTAPPLICATION_MEMORY_H
#define REDTEXTAPPLICATION_MEMORY_H
#include <atomic>

namespace RTF{
    namespace Types{

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

            T* data;
            std::atomic<size_t> counter;
            bool isLiteral;
        };
    }
}

#endif //REDTEXTAPPLICATION_MEMORY_H
