//
// Created by Гедерт Корней on 17.08.2021.
//

#ifndef CMAKE_INSTALL_CMAKE_BASICUTF8STRING_H
#define CMAKE_INSTALL_CMAKE_BASICUTF8STRING_H

#include <RTD/Memory/Allocator.h>

namespace RTF {
    namespace Strings {
        template <typename T, class _allocator = Memory::Allocator<T>>
        class BasicUtf8String {
        public:
            BasicUtf8String();
            BasicUtf8String(const SharedString &string);
            BasicUtf8String(SharedString &&string) noexcept;
            BasicUtf8String(const char *str);

            BasicUtf8String &operator=(const SharedString &string);
            BasicUtf8String &operator=(SharedString &&string) noexcept;
            BasicUtf8String &operator=(const char *str);

            BasicUtf8String &operator()(const SharedString &string);
            BasicUtf8String &operator()(SharedString &&string);
            BasicUtf8String &operator()(const char *str);

            BasicUtf8String operator+(SharedString &&string);
            BasicUtf8String operator+(const SharedString &string);
            BasicUtf8String operator+(const char *str);

            BasicUtf8String &operator+=(SharedString &&string);
            BasicUtf8String &operator+=(const SharedString &string);
            BasicUtf8String &operator+=(const char *str);

            bool operator==(const SharedString &string);
            bool operator==(const char *str);

            bool operator!=(const SharedString &string);
            bool operator!=(const char *str);

            char &operator[](size_t i);

            explicit operator const char *();

            BasicUtf8String &ToUpper();
            BasicUtf8String &ToLower();

            size_t Size() const;
            ~BasicUtf8String();

        private:

        };
    }
}

#endif //CMAKE_INSTALL_CMAKE_BASICUTF8STRING_H
