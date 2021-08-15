//
// Created by kiper220 on 15.07.2021.
//

#ifndef REDTEXTAPPLICATION_SHAREDVECTOR_H
#define REDTEXTAPPLICATION_SHAREDVECTOR_H

#include <RTD/Types/ASharedPointer.h>
#include <cstdio>

namespace RTF{
    namespace Containers{
        template<typename T>
        class SharedVector{
        public:
            SharedVector(){
                this->data = new T[this->stepOfAllocate];
                this->allocatedMemory = this->stepOfAllocate;
            }

            SharedVector(const SharedVector& vector):   data(vector.data),
                                            lengthOfVector(vector.lengthOfVector),
                                            allocatedMemory(vector.allocatedMemory) {}
            SharedVector(const T* data, uint64_t length): data(data), lengthOfVector(length) {}
            SharedVector(SharedVector&& vector) noexcept :  data(vector.data), lengthOfVector(vector.lengthOfVector),
                                                allocatedMemory(vector.allocatedMemory), stepOfAllocate(vector.stepOfAllocate){
                vector.data.DestructThis();
                vector.lengthOfVector = 0;
                vector.allocatedMemory = 0;
                vector.stepOfAllocate = 25;
            }

            SharedVector& operator=(const SharedVector& vector){
                if(&vector != this) {
                    this->data = vector.data;
                    this->lengthOfVector = vector.lengthOfVector;
                    this->allocatedMemory = vector.allocatedMemory;
                }
                return *this;
            }
            SharedVector& operator=(SharedVector&& vector) noexcept {
                if(&vector != this) {
                    this->data = vector.data;
                    this->lengthOfVector = vector.lengthOfVector;
                    this->allocatedMemory = vector.allocatedMemory;
                    this->stepOfAllocate = vector.stepOfAllocate;

                    vector.data.DestructThis();
                    vector.lengthOfVector = 0;
                    vector.allocatedMemory = 0;
                    vector.stepOfAllocate = 25;
                }

                return *this;
            }

            SharedVector& operator()(const SharedVector& vector){
                if(&vector != this) {
                    this->data = vector.data;
                    this->lengthOfVector = vector.lengthOfVector;
                    this->allocatedMemory = vector.allocatedMemory;
                    return *this;
                }
                return *this;
            }
            SharedVector& operator()(SharedVector&& vector){
                if(&vector != this) {
                    this->data = vector.data;
                    this->lengthOfVector = vector.lengthOfVector;
                    this->allocatedMemory = vector.allocatedMemory;
                    this->stepOfAllocate = vector.stepOfAllocate;

                    vector.data.DestructThis();
                    vector.lengthOfVector = 0;
                    vector.allocatedMemory = 0;
                    vector.stepOfAllocate = 25;
                }
                return *this;
            }
            SharedVector& operator()(T* data, uint64_t length){
                this->data = data;
                this->lengthOfVector = length;
                this->allocatedMemory = length;
                return *this;
            }
            SharedVector& operator()(const T* data, uint64_t length){
                this->data = data;
                this->lengthOfVector = length;
                return *this;
            }
            bool Empty() const{
                return this->lengthOfVector == 0;
            }
            uint64_t Size() const{
                return this->lengthOfVector;
            }

            void PushBack(T& pushData){
                this->operator[](this->lengthOfVector) = pushData;
            }
            void PushBack(T pushData){
                this->operator[](this->lengthOfVector) = pushData;
            }

            void SetSize(uint64_t newSize){
                Types::ASharedPointer<T> temporaryVariable(new T[(newSize + 1) - ((newSize + 1) % this->stepOfAllocate) + this->stepOfAllocate]);
                uint64_t min = this->lengthOfVector < newSize ? this->lengthOfVector : newSize;

                for(uint64_t i = 0; i < min; i++)
                    temporaryVariable[i] = this->data[i];

                this->allocatedMemory = (newSize + 1) - ((newSize + 1) % this->stepOfAllocate) + this->stepOfAllocate;
                this->lengthOfVector = newSize;

                this->data = temporaryVariable;
            }
            void UnConstant(){
                if(!this->data.IsLiteral())
                    return;

                fprintf(stderr,"UnConstant: %lu\n", this->lengthOfVector - (this->lengthOfVector % this->stepOfAllocate) + this->stepOfAllocate);
                Types::ASharedPointer<T> tmp(new T[this->lengthOfVector - (this->lengthOfVector % this->stepOfAllocate) + this->stepOfAllocate]);

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
                Types::ASharedPointer<T> temporaryVariable = new T[newAllocation];

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
                if(this->data.IsLiteral() || this->allocatedMemory < i || !this->data.Alone()){
                    uint64_t size;
                    {
                        uint64_t tmp1, tmp2;
                        tmp1 = i - (i % this->stepOfAllocate) + this->stepOfAllocate;
                        tmp2 = this->allocatedMemory;
                        size = tmp1 > tmp2? tmp1 : tmp2;
                    }

                    Types::ASharedPointer<T> tmp(new T[size]);

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

            ~SharedVector() = default;
        private:
            Types::ASharedPointer<T> data;
            uint64_t lengthOfVector = 0;
            uint64_t allocatedMemory = 0;
            uint16_t stepOfAllocate = 25;
        };
    }
}

#endif //REDTEXTAPPLICATION_SHAREDVECTOR_H
