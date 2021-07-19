//
// Created by kiper220 on 11.07.2021.
//

#include <inttypes.h>

#ifndef REDTEXTAPPLICATION_APOINTER_H
#define REDTEXTAPPLICATION_APOINTER_H

namespace RTF {
    namespace Types{
        template<typename T>
        class APointer{
        public:
            typedef struct {
                T* data;
                uint64_t counter;
                bool is_Const;
            } pointer_t;

        public:
            APointer() = default;
            APointer(const APointer& aPointer){
                this->pointer = aPointer.pointer;
                this->pointer->counter++;
            }
            explicit APointer(T* memory){
                this->pointer = new pointer_t;
                this->pointer->data = memory;
                this->pointer->counter = 1;
                this->pointer->is_Const = false;
            }
            explicit APointer(const T* memory){
                this->pointer = new pointer_t;
                this->pointer->data = (char*)memory;
                this->pointer->counter = 1;
                this->pointer->is_Const = true;
            }

            APointer& operator=(const APointer& aPointer){
                this->DestructThis();

                this->pointer = aPointer.pointer;
                this->pointer->counter++;

                return *this;
            }
            APointer& operator=(T* memory){
                this->DestructThis();

                this->pointer = new pointer_t;
                this->pointer->data = memory;
                this->pointer->counter = 1;
                this->pointer->is_Const = false;

                return *this;
            }
            APointer& operator=(const T* memory){
                this->DestructThis();

                this->pointer = new pointer_t;
                this->pointer->data = (T*)memory;
                this->pointer->counter = 1;
                this->pointer->is_Const = true;

                return *this;
            }

            APointer& operator()(const APointer& aPointer){
                this->DestructThis();

                this->pointer = aPointer.pointer;
                this->pointer->counter++;

                return *this;
            }
            APointer& operator()(T* memory){
                this->DestructThis();

                this->pointer = new pointer_t;
                this->pointer->data = memory;
                this->pointer->counter = 1;
                this->pointer->is_Const = false;

                return *this;
            }
            APointer& operator()(const T* memory){
                this->DestructThis();

                this->pointer = new pointer_t;
                this->pointer->data = (T*)memory;
                this->pointer->counter = 1;
                this->pointer->is_Const = true;

                return *this;
            }

            bool Alone() const{
                if(this->pointer == nullptr)
                    throw;
                return this->pointer->counter == 1;
            }
            bool Empty() const{
                return this->pointer == nullptr;
            }
            bool IsConst() const{
                return this->pointer->is_Const;
            }

            void DestructThis(){
                if(this->pointer != nullptr){
                    this->pointer->counter--;
                    if(this->pointer->counter == 0 && !this->pointer->is_Const)
                        delete[] this->pointer->data,
                                delete this->pointer;
                    this->pointer == nullptr;
                }
            }
            T GetElement(uint64_t i) const{
                return this->pointer->data[i];
            }

            T& operator[](uint64_t i){
                if(this->pointer == nullptr)
                    throw;
                return this->pointer->data[i];
            }

            T* operator*(){
                if(this->pointer == nullptr)
                    throw;
                return this->pointer->data;
            }


            ~APointer(){
                this->DestructThis();
            }

        private:
            explicit APointer(const pointer_t &pointer1){
                this->pointer = pointer1;
                this->pointer->counter++;
            }

            pointer_t* pointer = nullptr;
        };
    }
}

#endif //REDTEXTAPPLICATION_APOINTER_H
