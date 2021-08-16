//
// Created by kiper220 on 23.07.2021.
//
#include <RTD/Types/Memory.h>
#include <stdio.h>

#ifndef REDTEXTAPPLICATION_SHAREDPOINTER_H
#define REDTEXTAPPLICATION_SHAREDPOINTER_H


namespace RTF {
    namespace Types{

        template<typename T>
        class SharedPointer{
        public:
            SharedPointer() = default;
            SharedPointer(const SharedPointer& aPointer): pointer(aPointer.pointer){
                if(this->pointer != nullptr){
                    this->pointer->counter++;
                }
            }

            SharedPointer(T* memory){
                if(memory == nullptr) return;
                this->pointer = new PointerType<T>(memory, 1, false);
            }
            SharedPointer(const T* memory){
                if(memory == nullptr) return;
                this->pointer = new PointerType<T>(memory, 1, true);
            }
            explicit SharedPointer(T &data){
                this->pointer = new PointerType<T>(data, 1, true);
            }

            SharedPointer& operator=(const SharedPointer& aPointer){
                this->DestructThis();
                if(aPointer.IsEmpty()) return *this;

                this->pointer = aPointer.pointer;
                this->pointer->counter++;

                return *this;
            }
            SharedPointer& operator=(T* memory){
                this->DestructThis();
                if(memory == nullptr) return *this;

                this->pointer = new PointerType<T>(memory, 1, false);

                return *this;
            }
            SharedPointer& operator=(const T* memory){
                this->DestructThis();
                if(memory == nullptr) return *this;

                this->pointer = new PointerType<T>(memory, 1, true);

                return *this;
            }
            SharedPointer& operator=(T& data){
                this->DestructThis();

                this->pointer = new PointerType<T>(data, 1, true);

                return *this;
            }

            SharedPointer& operator()(const SharedPointer& aPointer){
                this->DestructThis();
                if(aPointer.IsEmpty()) return *this;

                this->pointer = aPointer.pointer;
                this->pointer->counter++;

                return *this;
            }
            SharedPointer& operator()(T* memory){
                this->DestructThis();
                if(memory == nullptr) return *this;

                this->pointer = new PointerType<T>(memory, 1, false);

                return *this;
            }
            SharedPointer& operator()(const T* memory){
                this->DestructThis();
                if(memory == nullptr) return *this;

                this->pointer = new PointerType<T>(memory, 1, true);

                return *this;
            }

            bool operator==(const SharedPointer &pointer1) const{
                return this->pointer == pointer1.pointer;
            }
            bool operator==(const PointerType<T> *pointer1) const{
                return this->pointer == pointer1;
            }
            bool operator!=(const SharedPointer &pointer1) const{
                return this->pointer != pointer1.pointer;
            }
            bool operator!=(const PointerType<T> *pointer1) const{
                return this->pointer != pointer1;
            }

            bool Alone() const{
                if(this->pointer == nullptr)
                    throw 123;
                return this->pointer->counter == 1;
            }
            bool IsEmpty() const{
                return this->pointer == nullptr;
            }
            bool IsLiteral() const{
                if(this->pointer == nullptr)
                    throw 123;
                return this->pointer->isLiteral;
            }

            T& operator*(){
                if(this->pointer == nullptr)
                    throw 123;
                return *((T *) this->pointer->data);
            }

            void DestructThis(){
                if(this->pointer != nullptr){
                    if(--this->pointer->counter == 0) {
                        if(!this->pointer->isLiteral)
                            delete this->pointer->data;
                        delete this->pointer;
                    }
                }
                this->pointer = nullptr;
            }

            ~SharedPointer(){
                this->DestructThis();
            }

        private:
            explicit SharedPointer(const PointerType<T> &pointer1){
                this->pointer = pointer1;
                this->pointer->counter++;
            }

            PointerType<T>* pointer = nullptr;
        };
    }

#ifdef TESTS_ON
#include <RTF/Tests.h>

bool TEST(RTD, Types, SharedPointer)();

#endif
}

#endif //REDTEXTAPPLICATION_SHAREDPOINTER_H
