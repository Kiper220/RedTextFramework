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
                this->data = new T[this->stepOfAllocate];
                this->allocatedMemory = this->stepOfAllocate;
            }

            Vector(const Vector& vector){
                if(!vector.Empty() && !vector.isAlone){
                    this->data = vector.data;
                    this->lengthOfVector = vector.lengthOfVector;
                    this->allocatedMemory = vector.allocatedMemory;
                    this->isAlone = false;
                    return;
                }
                if(vector.Empty()){
                    this->data = new T[this->stepOfAllocate];
                    this->allocatedMemory = this->stepOfAllocate;
                    this->isAlone = false;
                    return;
                }

                this->data = new T[vector.lengthOfVector + this->stepOfAllocate];
                this->allocatedMemory = (vector.lengthOfVector + 1) - ((vector.lengthOfVector + 1) % this->stepOfAllocate) + this->stepOfAllocate;
                this->lengthOfVector = vector.lengthOfVector;
                this->isAlone = false;
            }
            Vector(Vector&& vector) noexcept {
                this->data = vector.data;
                this->lengthOfVector = vector.lengthOfVector;
                this->allocatedMemory = vector.allocatedMemory;
                this->stepOfAllocate = vector.stepOfAllocate;
                this->isAlone = vector.isAlone;

                vector.data.DestructThis();
                vector.lengthOfVector = 0;
                vector.allocatedMemory = 0;
                vector.stepOfAllocate = 25;
                vector.isAlone = false;
            }

            Vector& operator=(const Vector& vector){
                if(&vector != this) {
                    if (!vector.Empty() && !vector.isAlone) {
                        this->data = vector.data;
                        this->lengthOfVector = vector.lengthOfVector;
                        this->allocatedMemory = vector.allocatedMemory;
                        this->isAlone = false;
                        return *this;
                    }
                    if (vector.Empty()) {
                        this->data = new T[this->stepOfAllocate];
                        this->allocatedMemory = this->stepOfAllocate;
                        this->isAlone = false;
                        return *this;
                    }
                    this->data = new T[vector.lengthOfVector + this->stepOfAllocate];
                    this->allocatedMemory =
                            (vector.lengthOfVector + 1) - ((vector.lengthOfVector + 1) % this->stepOfAllocate) +
                            this->stepOfAllocate;
                    this->lengthOfVector = vector.lengthOfVector;
                    this->isAlone = false;
                }
                return *this;
            }
            Vector& operator=(Vector&& vector) noexcept {
                if(&vector != this) {
                    this->data = vector.data;
                    this->lengthOfVector = vector.lengthOfVector;
                    this->allocatedMemory = vector.allocatedMemory;
                    this->stepOfAllocate = vector.stepOfAllocate;
                    this->isAlone = vector.isAlone;

                    vector.data.DestructThis();
                    vector.lengthOfVector = 0;
                    vector.allocatedMemory = 0;
                    vector.stepOfAllocate = 25;
                    vector.isAlone = false;
                }

                return *this;
            }

            Vector& operator()(const Vector& vector){
                if(&vector != this) {
                    if (!vector.Empty() && !vector.isAlone) {
                        this->data = vector.data;
                        this->lengthOfVector = vector.lengthOfVector;
                        this->allocatedMemory = vector.allocatedMemory;
                        this->isAlone = false;
                        return *this;
                    }
                    if (vector.Empty()) {
                        this->data = new T[this->stepOfAllocate];
                        this->allocatedMemory = this->stepOfAllocate;
                        this->isAlone = false;
                        return *this;
                    }
                    this->data = new T[vector.lengthOfVector + this->stepOfAllocate];
                    this->allocatedMemory = vector.lengthOfVector + this->stepOfAllocate;
                    this->lengthOfVector = vector.lengthOfVector;
                    this->isAlone = false;
                }
                return *this;
            }
            Vector& operator()(Vector&& vector){
                if(&vector != this) {
                    this->data = vector.data;
                    this->lengthOfVector = vector.lengthOfVector;
                    this->allocatedMemory = vector.allocatedMemory;
                    this->stepOfAllocate = vector.stepOfAllocate;
                    this->isAlone = vector.isAlone;

                    vector.data.DestructThis();
                    vector.lengthOfVector = 0;
                    vector.allocatedMemory = 0;
                    vector.stepOfAllocate = 25;
                    vector.isAlone = false;
                }
                return *this;
            }
            Vector& operator()(T* data, uint64_t length){
                this->data = data;
                this->lengthOfVector = length;
                this->allocatedMemory = length;
                this->isAlone = false;
                return *this;
            }
            Vector& operator()(const T* data, uint64_t length){
                this->data = data;
                this->lengthOfVector = length;
                this->allocatedMemory = length;
                this->isAlone = false;
                return *this;
            }
            bool Empty() const{
                return this->lengthOfVector == 0;
            }
            uint64_t Size() const{
                return this->lengthOfVector;
            }

            void PushBack(const T& pushData){
                this->operator[](this->lengthOfVector) = pushData;
            }
            void PushBack(T pushData){
                this->operator[](this->lengthOfVector) = pushData;
            }
            void SetSize(uint64_t newSize){
                APointer<T> temporaryVariable(new T[(newSize + 1) - ((newSize + 1) % this->stepOfAllocate) + this->stepOfAllocate]);
                uint64_t min = this->lengthOfVector < newSize ? this->lengthOfVector : newSize;

                for(uint64_t i = 0; i < min; i++)
                    temporaryVariable[i] = this->data[i];

                this->allocatedMemory = (newSize + 1) - ((newSize + 1) % this->stepOfAllocate) + this->stepOfAllocate;
                this->lengthOfVector = newSize;

                this->data = temporaryVariable;
            }
            void UnConstant(){
                if(!this->data.IsConst())
                    return;

                APointer<T> tmp(new T[this->lengthOfVector - (this->lengthOfVector % this->stepOfAllocate) + this->stepOfAllocate]);

                for(uint64_t j = 0; j < this->lengthOfVector; j++)
                    tmp[j] = this->data[j];

                this->data = tmp;
                this->allocatedMemory = this->lengthOfVector - (this->lengthOfVector % this->stepOfAllocate) + this->stepOfAllocate;
            }
            void Erase(uint64_t start, uint64_t end){
                if(start == 0 && end == this->lengthOfVector){
                    this->data = new T[this->stepOfAllocate];
                    this->allocatedMemory = this->stepOfAllocate;
                    this->lengthOfVector = 0;
                    return;
                }
                if(start == end){
                    return;
                }
                if(start > end){
                    uint64_t tmp = start;
                    start = end;
                    end = tmp;
                }
                int newSize = this->lengthOfVector - (end - start);
                int newAllocation = (newSize + 1) - ((newSize + 1) % this->stepOfAllocate) + this->stepOfAllocate;
                APointer<T> temporaryVariable = new T[newAllocation];

                uint64_t i = 0;
                for(; i < start; i++){
                    temporaryVariable[i] = this->data[i];
                }
                for(; i < newSize; i++){
                    temporaryVariable[i] = this->data[i + (end - start)];
                }

                this->data = temporaryVariable;
                this->lengthOfVector = newSize;
                this->allocatedMemory = newAllocation;
            }

            T& operator[](uint64_t i){
                i++;
                if(this->data.IsConst() || this->allocatedMemory < i){
                    uint64_t size;
                    {
                        uint64_t tmp1, tmp2;
                        tmp1 = i - (i % this->stepOfAllocate) + this->stepOfAllocate;
                        tmp2 = this->allocatedMemory;
                        size = tmp1 > tmp2? tmp1 : tmp2;
                    }

                    APointer<T> tmp(new T[size]);

                    for(uint64_t j = 0; j < this->lengthOfVector; j++)
                        tmp[j] = this->data[j];

                    this->data = tmp;
                    this->allocatedMemory = size;
                }
                if(this->lengthOfVector < i)
                    this->lengthOfVector = i;
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
            uint64_t lengthOfVector = 0;
            uint64_t allocatedMemory = 0;
            uint16_t stepOfAllocate = 25;
            bool isAlone = false;
        };
    }
}

#endif //REDTEXTAPPLICATION_VECTOR_H
