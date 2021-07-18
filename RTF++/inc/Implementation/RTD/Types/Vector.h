//
// Created by kiper220 on 15.07.2021.
//

#ifndef REDTEXTAPPLICATION_VECTOR_H
#define REDTEXTAPPLICATION_VECTOR_H

#include <Implementation/RTD/Types/APointer.h>

namespace RTF{
    namespace Types{
        template<typename T>
        class Vector{
        public:
            Vector(){
                this->data = new T[this->step];
                this->allocated = this->step;
            }

            Vector(const Vector& vector){
                if(!vector.Empty() && !vector.alone){
                    this->data = vector.data;
                    this->length = vector.length;
                    this->allocated = vector.allocated;
                    this->alone = false;
                    return;
                }
                if(vector.Empty()){
                    this->data = new T[this->step];
                    this->allocated = this->step;
                    this->alone = false;
                    return;
                }
                this->data = new T[vector.length + this->step];
                this->allocated = (vector.length + 1) - ((vector.length + 1) % this->step) + this->step;
                this->length = vector.length;
                this->alone = false;
            }
            Vector(Vector&& vector) noexcept {
                this->data = vector.data;
                this->length = vector.length;
                this->allocated = vector.allocated;
                this->step = vector.step;
                this->alone = vector.alone;

                vector.data.DestructThis();
                vector.length = 0;
                vector.allocated = 0;
                vector.step = 25;
                vector.alone = false;
            }

            Vector& operator=(const Vector& vector){
                if(!vector.Empty() && !vector.alone){
                    this->data = vector.data;
                    this->length = vector.length;
                    this->allocated = vector.allocated;
                    this->alone = false;
                    return *this;
                }
                if(vector.Empty()){
                    this->data = new T[this->step];
                    this->allocated = this->step;
                    this->alone = false;
                    return *this;
                }
                this->data = new T[vector.length + this->step];
                this->allocated = (vector.length + 1) - ((vector.length + 1) % this->step) + this->step;
                this->length = vector.length;
                this->alone = false;
                return *this;
            }
            Vector& operator=(Vector&& vector) noexcept {
                this->data = vector.data;
                this->length = vector.length;
                this->allocated = vector.allocated;
                this->step = vector.step;
                this->alone = vector.alone;

                vector.data.DestructThis();
                vector.length = 0;
                vector.allocated = 0;
                vector.step = 25;
                vector.alone = false;

                return *this;
            }

            Vector& operator()(const Vector& vector){
                if(!vector.Empty() && !vector.alone){
                    this->data = vector.data;
                    this->length = vector.length;
                    this->allocated = vector.allocated;
                    this->alone = false;
                    return *this;
                }
                if(vector.Empty()){
                    this->data = new T[this->step];
                    this->allocated = this->step;
                    this->alone = false;
                    return *this;
                }
                this->data = new T[vector.length + this->step];
                this->allocated = vector.length + this->step;
                this->length = vector.length;
                this->alone = false;
                return *this;
            }
            Vector& operator()(Vector&& vector){
                this->data = vector.data;
                this->length = vector.length;
                this->allocated = vector.allocated;
                this->step = vector.step;
                this->alone = vector.alone;

                vector.data.DestructThis();
                vector.length = 0;
                vector.allocated = 0;
                vector.step = 25;
                vector.alone = false;
                return *this;
            }
            Vector& operator()(T* data, uint64_t length){
                this->data = data;
                this->length = length;
                this->allocated = length;
                this->alone = false;
                return *this;
            }
            Vector& operator()(const T* data, uint64_t length){
                this->data = data;
                this->length = length;
                this->allocated = length;
                this->alone = false;
                return *this;
            }
            bool Empty() const{
                return this->length == 0;
            }
            uint64_t Size() const{
                return this->length;
            }

            void PushBack(T& data){
                this->operator[](this->length) = data;
            }
            void PushBack(T data){
                this->operator[](this->length) = data;
            }
            void SetSize(uint64_t newSize){
                APointer<T> data = new T[(newSize + 1) - ((newSize + 1) % this->step) + this->step];
                uint64_t min = this->length < newSize? this->length : newSize;

                for(uint64_t i; i < min; i++)
                    data[i] = this->data[i];

                this->allocated = (newSize + 1) - ((newSize + 1) % this->step) + this->step;
                this->length = newSize;

                this->data = data;
            }
            void UnConstant(){
                if(!this->data.IsConst())
                    return;
                APointer<T> tmp = new T[this->length - (this->length % this->step) + this->step];
                for(uint64_t j = 0; j < this->length; j++)
                    tmp[j] = this->data[j];

                this->data = tmp;
                this->allocated = this->length - (this->length % this->step) + this->step;
            }
            void Erase(uint64_t start, uint64_t end){
                if(start == 0 && end == this->length){
                    this->data = new T[this->step];
                    this->allocated = this->step;
                    this->length = 0;
                    return;
                }
                if(start == end){
                    return;
                }
                if(start > end){
                    int tmp = start;
                    start = end;
                    end = tmp;
                }
                int newSize = this->length - (end - start);
                int newAllocation = (newSize + 1) - ((newSize + 1) % this->step) + this->step;
                APointer<T> data = new T[newAllocation];

                uint64_t i = 0;
                for(; i < start; i++){
                    data[i] = this->data[i];
                }
                for(; i < newSize; i++){
                    data[i] = this->data[i + (end - start)];
                }

                this->data = data;
                this->length = newSize;
                this->allocated = newAllocation;
            }

            T& operator[](uint64_t i){
                i++;
                if(this->data.IsConst() || this->allocated < i){
                    uint64_t size = 0;
                    {
                        uint64_t tmp1, tmp2;
                        tmp1 = i - (i % this->step) + this->step;
                        tmp2 = this->allocated;
                        size = tmp1 > tmp2? tmp1 : tmp2;
                    }

                    APointer<T> tmp = new T[size];
                    for(uint64_t j = 0; j < this->length; j++)
                        tmp[j] = this->data[j];

                    this->data = tmp;
                    this->allocated = size;
                }
                {
                    if(this->length < i)
                        this->length = i;
                };
                return this->data[i - 1];
            }

            T GetElement(uint64_t i) const{
                return this->data.GetElement(i);
            }

            T* operator*(){
                return *(this->data);
            }

            ~Vector() = default;
        private:
            APointer<T> data;
            uint64_t length = 0;
            uint64_t allocated = 0;
            uint16_t step = 25;
            bool alone = false;
        };
    }
}

#endif //REDTEXTAPPLICATION_VECTOR_H
