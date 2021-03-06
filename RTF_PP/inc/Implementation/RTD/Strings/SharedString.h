//
// Created by kiper220 on 11.07.2021.
//

#ifndef REDTEXTAPPLICATION_SHAREDSTRING_H
#define REDTEXTAPPLICATION_SHAREDSTRING_H
#include <RTD/Containers/SharedVector.h>

namespace RTF {
    namespace Strings {

        unsigned char *StringToLowerExt(unsigned char *pString);
        unsigned char *StringToUpperExt(unsigned char *pString);

        class SharedString{
        public:
            SharedString();
            SharedString(const SharedString& string);
            SharedString(SharedString&& string) noexcept;
            SharedString(const char* str);

            SharedString& operator=(const SharedString& string);
            SharedString& operator=(SharedString&& string) noexcept;
            SharedString& operator=(const char* str);

            SharedString& operator()(const SharedString& string);
            SharedString& operator()(SharedString&& string);
            SharedString& operator()(const char* str);

            SharedString operator+(SharedString &&string);
            SharedString operator+(const SharedString& string);
            SharedString operator+(const char* str);

            SharedString& operator+=(SharedString&& string);
            SharedString& operator+=(const SharedString& string);
            SharedString& operator+=(const char* str);

            bool operator==(const SharedString& string);
            bool operator==(const char* str);

            bool operator!=(const SharedString& string);
            bool operator!=(const char* str);

            char& operator[](size_t i);

            explicit operator const char*();

            SharedString& ToUpper();
            SharedString& ToLower();

            size_t Size() const;

            ~SharedString();

        private:
            Containers::SharedVector<char> string;
        };
    }
#ifdef TESTS_ON
bool TEST(RTD, Strings, SharedString)();
#endif
}

#endif //REDTEXTAPPLICATION_SHAREDSTRING_H
