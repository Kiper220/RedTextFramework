//
// Created by kiper220 on 11.07.2021.
//

#ifndef REDTEXTAPPLICATION_STRING_H
#define REDTEXTAPPLICATION_STRING_H
#include <Implementation/RTD/Types/Vector.h>

namespace RTF {
    namespace Strings {
        class String{
        public:
            String();
            String(const String& string);
            String(String&& string);
            explicit String(const char* str);

            String& operator=(const String& string);
            String& operator=(String&& string);
            String& operator=(const char* str);

            String& operator()(const String& string);
            String& operator()(String&& string);
            String& operator()(const char* str);

            String operator+(const String& string);
            String operator+(const char* str);

            String& operator+=(const String& string);
            String& operator+=(const char* str);

            bool operator==(const String& string);
            bool operator==(const char* str);

            operator const char*();

            String& ToUpper();
            String& ToLower();

            uint64_t Size() const;

            ~String();

        private:
            Types::Vector<char> string;
        };
    }
}

#endif //REDTEXTAPPLICATION_STRING_H
