//
// Created by Гедерт Корней on 17.08.2021.
//

#ifndef CMAKE_INSTALL_CMAKE_BASICUTF8STRING_H
#define CMAKE_INSTALL_CMAKE_BASICUTF8STRING_H

#include <RTD/Memory/Allocator.h>
#include <cstring>

namespace RTF {
    namespace Strings {
        template <typename T, class _allocator = Memory::BasicAllocator<T>>
        class BasicUtf8String {
        public:
            BasicUtf8String() = default;
            BasicUtf8String(const BasicUtf8String &string): datas(string.datas) {}
            BasicUtf8String(BasicUtf8String &&string) noexcept: datas(string.datas)  {}
            BasicUtf8String(size_t length): datas(length) {}
            BasicUtf8String(const T *str): datas(str, strlen(str) + 1) {}

            BasicUtf8String &operator=(const BasicUtf8String &string) {
                this->datas = string.datas;
                return *this;
            }
            BasicUtf8String &operator=(BasicUtf8String &&string) noexcept {
                this->datas = string.datas;
                return *this;
            }
            BasicUtf8String &operator=(const T *str) {
                this->datas.Set(str, strlen(str) + 1);
                return *this;
            }

            BasicUtf8String &operator()(const BasicUtf8String &string) {
                *this = string;
                return *this;
            }
            BasicUtf8String &operator()(BasicUtf8String &&string) {
                *this = string;
                return *this;
            }
            BasicUtf8String &operator()(const char *str) {
                *this = str;
                return *this;
            }

            BasicUtf8String &operator+=(BasicUtf8String &&string) {
                if(this->datas.begin().GetPointer() == (T*)nullptr || this->datas.cend().GetId() == 0){
                    this->datas = string.datas;
                    return *this;
                }
                size_t id = this->datas.end().GetPointer() - 1;
                this->datas.Allocate(this->datas.end().GetId() + string.datas.cend().GetId() - 1);
                Memory::MemCopy<true>(id, string.datas.cbegin().GetPointer(), string.datas.cend().GetId() * sizeof(T));

                return *this;
            }
            BasicUtf8String &operator+=(const BasicUtf8String &string) {
                if(this->datas.begin().GetPointer() == (T*)nullptr || this->datas.cend().GetId() == 0){
                    this->datas = string.datas;
                    return *this;
                }
                auto id = this->datas.end().GetPointer() - 1;
                this->datas.Allocate(this->datas.end().GetId() + string.datas.cend().GetId() - 1);
                Memory::MemCopy<true>(id, string.datas.cbegin().GetPointer(), string.datas.cend().GetId() * sizeof(T));

                return *this;
            }
            BasicUtf8String &operator+=(const char *str) {
                size_t length = strlen(str) + 1;

                if(this->datas.begin().GetPointer() == (T*)nullptr || this->datas.cend().GetId() == 0){
                    this->datas.Set(str, length);
                    return *this;
                }
                auto id = this->datas.end().GetPointer() - 1;
                this->datas.Allocate(this->datas.end().GetId() + length - 1);
                Memory::MemCopy<true>(id, this->datas.end().GetPointer() - 2, str, length * sizeof(T));

                return *this;
            }

            BasicUtf8String operator+(BasicUtf8String &&string) const{
                BasicUtf8String tmp = *this;
                tmp += string;

                return tmp;
            }
            BasicUtf8String operator+(const BasicUtf8String &string) const{
                BasicUtf8String tmp = *this;
                tmp += string;

                return tmp;
            }
            BasicUtf8String operator+(const char *str) const{
                BasicUtf8String tmp = *this;
                tmp += str;

                return tmp;
            }

            bool operator==(const BasicUtf8String &string) {
                if(this->datas.end().GetId() != string.datas.cend().GetId())
                    return false;
                for(typename Memory::BasicAllocator<T>::Iterator begin = this->datas.begin(); begin != this->datas.end(); begin++){
                    if(*begin != *(string.datas.cbegin() + begin))
                        return false;
                }
                return true;
            }
            bool operator==(const char *str) {
                size_t length = strlen(str) + 1;

                if(this->datas.end().GetId() != length)
                    return false;
                for(typename Memory::BasicAllocator<T>::Iterator begin = this->datas.begin(); begin != this->datas.end(); begin++){
                    if(*begin != str[begin.GetId()])
                        return false;
                }
                return true;
            }

            bool operator!=(const BasicUtf8String &string) {
                return !(*this == string);
            }
            bool operator!=(const char *str) {
                return !(*this == str);
            }

            T &operator[](size_t i) {
                return this->datas[i];
            }

            operator char *(){
                return this->datas.begin();
            }

            BasicUtf8String &ToUpper(){

                return *this;
            }
            BasicUtf8String &ToLower(){

                return *this;
            }

            size_t Size() const {
                return this->datas.end().GetId() - 1;
            }
            ~BasicUtf8String() = default;

        private:
            Memory::BasicAllocator<T> datas;
        };
    }
#ifdef TESTS_ON
    bool TEST(RTD, Strings, BasicUtf8String)();
#endif
}

#endif //CMAKE_INSTALL_CMAKE_BASICUTF8STRING_H
