//
// Created by kiper220 on 11.07.2021.
//

#include <RTD/Types/Memory.h>
#include <stdexcept>

#ifndef REDTEXTAPPLICATION_APOINTER_H
#define REDTEXTAPPLICATION_APOINTER_H

namespace RTF {
    namespace Types{
        template<typename T>
        class ASharedPointer{
        public:
            ASharedPointer() noexcept = default;
            ASharedPointer(const ASharedPointer& aPointer) noexcept: pointer(aPointer.pointer){
                if(this->pointer != nullptr){
                    this->pointer->counter++;
                }
            }
            ASharedPointer(T* memory) noexcept{
                if(memory == nullptr) return;

                this->pointer = new PointerType<T>;
                this->pointer->data = memory;
                this->pointer->counter = 1;
                this->pointer->isLiteral = false;
            }
            ASharedPointer(const T* memory) noexcept{
                if(memory == nullptr) return;

                this->pointer = new PointerType<T>;
                this->pointer->data = (T*)memory;
                this->pointer->counter = 1;
                this->pointer->isLiteral = true;
            }

            ASharedPointer& operator=(const ASharedPointer& aPointer) noexcept{
                this->DestructThis();
                if(aPointer.IsEmpty()) return *this;

                this->pointer = aPointer.pointer;
                this->pointer->counter++;

                return *this;
            }
            ASharedPointer& operator=(T* memory) noexcept{
                this->DestructThis();
                if(memory == nullptr) return *this;

                this->pointer = new PointerType<T>;
                this->pointer->data = memory;
                this->pointer->counter = 1;
                this->pointer->isLiteral = false;

                return *this;
            }
            ASharedPointer& operator=(const T* memory) noexcept{
                this->DestructThis();
                if(memory == nullptr) return *this;

                this->pointer = new PointerType<T>;
                this->pointer->data = (T*)memory;
                this->pointer->counter = 1;
                this->pointer->isLiteral = true;

                return *this;
            }

            ASharedPointer& operator()(const ASharedPointer& aPointer) noexcept{
                this->DestructThis();
                if(aPointer.IsEmpty()) return *this;

                this->pointer = aPointer.pointer;
                this->pointer->counter++;

                return *this;
            }
            ASharedPointer& operator()(T* memory) noexcept{
                this->DestructThis();
                if(memory == nullptr) return *this;

                this->pointer = new PointerType<T>(memory, 1, false);

                return *this;
            }
            ASharedPointer& operator()(const T* memory) noexcept{
                this->DestructThis();
                if(memory == nullptr) return *this;

                this->pointer = new PointerType<T>((T*)memory, 1, true);

                return *this;
            }

            bool operator==(const ASharedPointer &pointer1) noexcept{
                return this->pointer == pointer1.pointer;
            }
            bool operator==(const PointerType<T> *pointer1) noexcept{
                return this->pointer == pointer1;
            }
            bool operator!=(const ASharedPointer &pointer1) noexcept{
                return this->pointer != pointer1.pointer;
            }
            bool operator!=(const PointerType<T> *pointer1) noexcept{
                return this->pointer != pointer1;
            }


            bool Alone() const{
                if(this->pointer == nullptr)
                    throw;
                return this->pointer->counter == 1;
            }
            bool IsEmpty() const noexcept{
                return this->pointer == nullptr;
            }
            bool IsLiteral() const{
                if(this->pointer == nullptr)
                    throw std::runtime_error("Pointer equal nullptr!");
                return this->pointer->isLiteral;
            }

            void DestructThis() noexcept {
                if(this->pointer != nullptr){
                    if(--this->pointer->counter == 0){
                        if(!this->pointer->isLiteral)
                            delete[] this->pointer->data;
                        delete this->pointer;
                    }
                }
                this->pointer = nullptr;
            }
            T GetElement(size_t i) const{
                return ((T*)this->pointer->data)[i];
            }

            T& operator[](size_t i){
                if(this->pointer == nullptr)
                    throw;
                return ((T*)this->pointer->data)[i];
            }

            T* operator*(){
                if(this->pointer == nullptr)
                    throw std::runtime_error("Pointer equal nullptr!");
                return ((T*)this->pointer->data);
            }


            ~ASharedPointer(){
                this->DestructThis();
            }

        private:
            explicit ASharedPointer(const PointerType<T> &pointer1){
                this->pointer = pointer1;
                this->pointer->counter++;
            }

            PointerType<T>* pointer = nullptr;
        };
    }
#ifdef TESTS_ON
#include <RTF/Tests.h>

bool TEST(RTD, Types, ASharedPointer)();

#endif
}

#endif //REDTEXTAPPLICATION_APOINTER_H
