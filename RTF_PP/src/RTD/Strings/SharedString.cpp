//
// Created by kiper220 on 15.07.2021.
//

#include <RTD/Strings/SharedString.h>
#include <cstring>
#ifdef TESTS_ON
void test();

#endif

namespace RTF {
    namespace Strings {

        SharedString::SharedString() = default;

        SharedString::SharedString(const SharedString &string): string(string.string) {}

        SharedString::SharedString(SharedString &&string) noexcept: string((Containers::SharedVector<char>&&)string.string) {}

        SharedString::SharedString(const char *str): string(str, strlen(str) + 1){}

        SharedString &SharedString::operator=(const SharedString &string) {
            this->string = string.string;
            return *this;
        }

        SharedString &SharedString::operator=(SharedString &&string) noexcept{
            this->string = (Containers::SharedVector<char>&&)string.string;
            return *this;
        }

        SharedString &SharedString::operator=(const char *str) {
            this->string(str, strlen(str) + 1);
            return *this;
        }

        SharedString &SharedString::operator()(const SharedString &string) {
            this->string = string.string;
            return *this;
        }

        SharedString &SharedString::operator()(SharedString &&string) {
            this->string = (Containers::SharedVector<char>&&)string.string;
            return *this;
        }

        SharedString &SharedString::operator()(const char *str) {
            this->string(str, strlen(str) + 1);
            return *this;
        }

        SharedString SharedString::operator+(SharedString &&string) {
            SharedString tmp = (SharedString&&)string;
            return *this + tmp;
        }
        SharedString SharedString::operator+(const SharedString &string) {
            SharedString str;
            str.string.SetSize(this->Size() + string.Size() + 1);
            size_t i = 0;

            for(; i < this->string.Size(); i++){
                str.string[i] = this->string[i];
            }

            for(size_t j = 0; j <= string.Size(); i++, j++){
                str.string[i] = string.string.GetElement(j);
            }

            return str;
        }

        SharedString SharedString::operator+(const char *string1) {
            SharedString str;
            size_t size = strlen(string1) + 1;

            str.string.SetSize(this->Size() + size);
            size_t i = 0;

            for(; i < this->string.Size(); i++){
                str.string[i] = this->string[i];
            }

            for(size_t j = 0; j <= size; i++, j++){
                str.string[i] = string1[j];
            }

            return str;
        }

        SharedString &SharedString::operator+=(SharedString &&string){
            SharedString tmp = (SharedString&&)string;
            return *this += tmp;
        }
        SharedString &SharedString::operator+=(const SharedString &string) {
            *this = *this + string;
            return *this;
        }

        SharedString &SharedString::operator+=(const char *str) {
            *this = *this + str;
            return *this;
        }


        bool SharedString::operator==(const SharedString& string) {
            if(this->Size() != string.Size())
                return false;
            for(size_t i = 0; i < this->string.Size(); i++)
                if((*this->string)[i] != (*((Containers::SharedVector<char>&)string.string))[i]){
                    printf("%d != %d", (*this->string)[i], (*((Containers::SharedVector<char>&)string.string))[i]);
                    return false;
                }

            return true;
        }
        bool SharedString::operator==(const char* str) {
            if(this->Size() != strlen(str))
                return false;
            for(size_t i = 0; i < this->string.Size(); i++)
                if((*this->string)[i] != str[i])
                    return false;

            return true;
        }


        bool SharedString::operator!=(const SharedString& string) {
            return !(*this == string);
        }
        bool SharedString::operator!=(const char* str) {
            return !(*this == str);
        }

        char& SharedString::operator[](size_t i){
            return this->string[i];
        }

        SharedString::operator const char*(){
            return *this->string;
        }

        SharedString &SharedString::ToUpper() {
            this->string.UnConstant();
            StringToUpperExt((unsigned char*)(*this->string));
            return *this;
        }

        SharedString &SharedString::ToLower() {
            this->string.UnConstant();
            StringToLowerExt((unsigned char*)(*this->string));
            return *this;
        }

        size_t SharedString::Size() const{
            return this->string.Size() - 1;
        }

        SharedString::~SharedString() = default;

        unsigned char *StringToLowerExt(unsigned char *pString) { // TODO: Refactor StringToLowerExt function;
            if (pString && *pString) {
                unsigned char *p = pString;
                unsigned char *pExtChar = 0;
                while (*p) {
                    if ((*p >= 0x41) && (*p <= 0x5a)) // US ASCII
                        (*p) += 0x20;
                    else if (*p > 0xc0) {
                        pExtChar = p;
                        p++;
                        switch (*pExtChar) {
                            case 0xc3: // Latin 1
                                if ((*p >= 0x80)
                                    && (*p <= 0x9e)
                                    && (*p != 0x97))
                                    (*p) += 0x20; // US ASCII shift
                                break;
                            case 0xc4: // Latin Exteneded
                                if ((*p >= 0x80)
                                    && (*p <= 0xb7)
                                    && (!(*p % 2))) // Even
                                    (*p)++; // Next char is lwr
                                else if ((*p >= 0xb9)
                                         && (*p <= 0xbe)
                                         && (*p % 2)) // Odd
                                    (*p)++; // Next char is lwr
                                else if (*p == 0xbf) {
                                    *pExtChar = 0xc5;
                                    (*p) = 0x80;
                                }
                                break;
                            case 0xc5: // Latin Exteneded
                                if ((*p >= 0x80)
                                    && (*p <= 0x88)
                                    && (*p % 2)) // Odd
                                    (*p)++; // Next char is lwr
                                else if ((*p >= 0x8a)
                                         && (*p <= 0xb7)
                                         && (!(*p % 2))) // Even
                                    (*p)++; // Next char is lwr
                                else if ((*p >= 0xb9)
                                         && (*p <= 0xbe)
                                         && (*p % 2)) // Odd
                                    (*p)++; // Next char is lwr
                                break;
                            case 0xc6: // Latin Exteneded
                                switch (*p) {
                                    case 0x82:
                                    case 0x84:
                                    case 0x87:
                                    case 0x8b:
                                    case 0x91:
                                    case 0x98:
                                    case 0xa0:
                                    case 0xa2:
                                    case 0xa4:
                                    case 0xa7:
                                    case 0xac:
                                    case 0xaf:
                                    case 0xb3:
                                    case 0xb5:
                                    case 0xb8:
                                    case 0xbc:
                                        (*p)++; // Next char is lwr
                                        break;
                                    default:
                                        break;
                                }
                                break;
                            case 0xc7: // Latin Exteneded
                                if (*p == 0x84)
                                    (*p) = 0x86;
                                else if (*p == 0x85)
                                    (*p)++; // Next char is lwr
                                else if (*p == 0x87)
                                    (*p) = 0x89;
                                else if (*p == 0x88)
                                    (*p)++; // Next char is lwr
                                else if (*p == 0x8a)
                                    (*p) = 0x8c;
                                else if (*p == 0x8b)
                                    (*p)++; // Next char is lwr
                                else if ((*p >= 0x8d)
                                         && (*p <= 0x9c)
                                         && (*p % 2)) // Odd
                                    (*p)++; // Next char is lwr
                                else if ((*p >= 0x9e)
                                         && (*p <= 0xaf)
                                         && (!(*p % 2))) // Even
                                    (*p)++; // Next char is lwr
                                else if (*p == 0xb1)
                                    (*p) = 0xb3;
                                else if (*p == 0xb2)
                                    (*p)++; // Next char is lwr
                                else if (*p == 0xb4)
                                    (*p)++; // Next char is lwr
                                else if (*p == 0xb8)
                                    (*p)++; // Next char is lwr
                                else if (*p == 0xba)
                                    (*p)++; // Next char is lwr
                                else if (*p == 0xbc)
                                    (*p)++; // Next char is lwr
                                else if (*p == 0xbe)
                                    (*p)++; // Next char is lwr
                                break;
                            case 0xc8: // Latin Exteneded
                                if ((*p >= 0x80)
                                    && (*p <= 0x9f)
                                    && (!(*p % 2))) // Even
                                    (*p)++; // Next char is lwr
                                else if ((*p >= 0xa2)
                                         && (*p <= 0xb3)
                                         && (!(*p % 2))) // Even
                                    (*p)++; // Next char is lwr
                                else if (*p == 0xbb)
                                    (*p)++; // Next char is lwr
                                break;
                            case 0xcd: // Greek & Coptic
                                switch (*p) {
                                    case 0xb0:
                                    case 0xb2:
                                    case 0xb6:
                                        (*p)++; // Next char is lwr
                                        break;
                                    default:
                                        if (*p == 0xbf) {
                                            *pExtChar = 0xcf;
                                            (*p) = 0xb3;
                                        }
                                        break;
                                }
                                break;
                            case 0xce: // Greek & Coptic
                                if (*p == 0x86)
                                    (*p) = 0xac;
                                else if (*p == 0x88)
                                    (*p) = 0xad;
                                else if (*p == 0x89)
                                    (*p) = 0xae;
                                else if (*p == 0x8a)
                                    (*p) = 0xaf;
                                else if (*p == 0x8c) {
                                    *pExtChar = 0xcf;
                                    (*p) = 0x8c;
                                } else if (*p == 0x8e) {
                                    *pExtChar = 0xcf;
                                    (*p) = 0x8d;
                                } else if (*p == 0x8f) {
                                    *pExtChar = 0xcf;
                                    (*p) = 0x8e;
                                } else if ((*p >= 0x91)
                                           && (*p <= 0x9f))
                                    (*p) += 0x20; // US ASCII shift
                                else if ((*p >= 0xa0)
                                         && (*p <= 0xab)
                                         && (*p != 0xa2)) {
                                    *pExtChar = 0xcf;
                                    (*p) -= 0x20;
                                }
                                break;
                            case 0xcf: // Greek & Coptic
                                if (*p == 0x8f)
                                    (*p) = 0xb4;
                                else if (*p == 0x91)
                                    (*p)++; // Next char is lwr
                                else if ((*p >= 0x98)
                                         && (*p <= 0xaf)
                                         && (!(*p % 2))) // Even
                                    (*p)++; // Next char is lwr
                                else if (*p == 0xb4)
                                    (*p) = 0x91;
                                else if (*p == 0xb7)
                                    (*p)++; // Next char is lwr
                                else if (*p == 0xb9)
                                    (*p) = 0xb2;
                                else if (*p == 0xbb)
                                    (*p)++; // Next char is lwr
                                else if (*p == 0xbd) {
                                    *pExtChar = 0xcd;
                                    (*p) = 0xbb;
                                } else if (*p == 0xbe) {
                                    *pExtChar = 0xcd;
                                    (*p) = 0xbc;
                                } else if (*p == 0xbf) {
                                    *pExtChar = 0xcd;
                                    (*p) = 0xbd;
                                }

                                break;
                            case 0xd0: // Cyrillic
                                if ((*p >= 0x80)
                                    && (*p <= 0x8f)) {
                                    *pExtChar = 0xd1;
                                    (*p) += 0x10;
                                } else if ((*p >= 0x90)
                                           && (*p <= 0x9f))
                                    (*p) += 0x20; // US ASCII shift
                                else if ((*p >= 0xa0)
                                         && (*p <= 0xaf)) {
                                    *pExtChar = 0xd1;
                                    (*p) -= 0x20;
                                }
                                break;
                            case 0xd1: // Cyrillic supplement
                                if ((*p >= 0xa0)
                                    && (*p <= 0xbf)
                                    && (!(*p % 2))) // Even
                                    (*p)++; // Next char is lwr
                                break;
                            case 0xd2: // Cyrillic supplement
                                if (*p == 0x80)
                                    (*p)++; // Next char is lwr
                                else if ((*p >= 0x8a)
                                         && (*p <= 0xbf)
                                         && (!(*p % 2))) // Even
                                    (*p)++; // Next char is lwr
                                break;
                            case 0xd3: // Cyrillic supplement
                                if ((*p >= 0x81)
                                    && (*p <= 0x8e)
                                    && (*p % 2)) // Odd
                                    (*p)++; // Next char is lwr
                                else if ((*p >= 0x90)
                                         && (*p <= 0xbf)
                                         && (!(*p % 2))) // Even
                                    (*p)++; // Next char is lwr
                                break;
                            case 0xd4: // Cyrillic supplement & Armenian
                                if ((*p >= 0x80)
                                    && (*p <= 0xaf)
                                    && (!(*p % 2))) // Even
                                    (*p)++; // Next char is lwr
                                else if ((*p >= 0xb1)
                                         && (*p <= 0xbf)) {
                                    *pExtChar = 0xd5;
                                    (*p) -= 0x10;
                                }
                                break;
                            case 0xd5: // Armenian
                                if ((*p >= 0x80)
                                    && (*p <= 0x96)
                                    && (!(*p % 2))) // Even
                                    (*p)++; // Next char is lwr
                                break;
                            case 0xe1: // Three byte code
                                pExtChar = p;
                                p++;
                                switch (*pExtChar) {
                                    case 0x82: // Georgian
                                        if ((*p >= 0xa0)
                                            && (*p <= 0xbf)) {
                                            *pExtChar = 0x83;
                                            (*p) -= 0x10;
                                        }
                                        break;
                                    case 0x83: // Georgian
                                        if ((*p >= 0x80)
                                            && ((*p <= 0x85)
                                                || (*p == 0x87))
                                            || (*p == 0x8d))
                                            (*p) += 0x30;
                                        break;
                                    case 0xb8: // Latin extened
                                        if ((*p >= 0x80)
                                            && (*p <= 0xbf)
                                            && (!(*p % 2))) // Even
                                            (*p)++; // Next char is lwr
                                        break;
                                    case 0xb9: // Latin extened
                                        if ((*p >= 0x80)
                                            && (*p <= 0xbf)
                                            && (!(*p % 2))) // Even
                                            (*p)++; // Next char is lwr
                                        break;
                                    case 0xba: // Latin extened
                                        if ((*p >= 0x80)
                                            && (*p <= 0x94)
                                            && (!(*p % 2))) // Even
                                            (*p)++; // Next char is lwr
                                        else if ((*p >= 0x9e)
                                                 && (*p <= 0xbf)
                                                 && (!(*p % 2))) // Even
                                            (*p)++; // Next char is lwr
                                        break;
                                    case 0xbb: // Latin extened
                                        if ((*p >= 0x80)
                                            && (*p <= 0xbf)
                                            && (!(*p % 2))) // Even
                                            (*p)++; // Next char is lwr
                                        break;
                                    case 0xbc: // Greek extened
                                        if ((*p >= 0x88)
                                            && (*p <= 0x8f))
                                            (*p) -= 0x08;
                                        else if ((*p >= 0x98)
                                                 && (*p <= 0x9f))
                                            (*p) -= 0x08;
                                        else if ((*p >= 0xa8)
                                                 && (*p <= 0xaf))
                                            (*p) -= 0x08;
                                        else if ((*p >= 0xb8)
                                                 && (*p <= 0x8f))
                                            (*p) -= 0x08;
                                        break;
                                    case 0xbd: // Greek extened
                                        if ((*p >= 0x88)
                                            && (*p <= 0x8d))
                                            (*p) -= 0x08;
                                        else if ((*p >= 0x98)
                                                 && (*p <= 0x9f))
                                            (*p) -= 0x08;
                                        else if ((*p >= 0xa8)
                                                 && (*p <= 0xaf))
                                            (*p) -= 0x08;
                                        else if ((*p >= 0xb8)
                                                 && (*p <= 0x8f))
                                            (*p) -= 0x08;
                                        break;
                                    case 0xbe: // Greek extened
                                        if ((*p >= 0x88)
                                            && (*p <= 0x8f))
                                            (*p) -= 0x08;
                                        else if ((*p >= 0x98)
                                                 && (*p <= 0x9f))
                                            (*p) -= 0x08;
                                        else if ((*p >= 0xa8)
                                                 && (*p <= 0xaf))
                                            (*p) -= 0x08;
                                        else if ((*p >= 0xb8)
                                                 && (*p <= 0xb9))
                                            (*p) -= 0x08;
                                        break;
                                    case 0xbf: // Greek extened
                                        if ((*p >= 0x88)
                                            && (*p <= 0x8c))
                                            (*p) -= 0x08;
                                        else if ((*p >= 0x98)
                                                 && (*p <= 0x9b))
                                            (*p) -= 0x08;
                                        else if ((*p >= 0xa8)
                                                 && (*p <= 0xac))
                                            (*p) -= 0x08;
                                        break;
                                    default:
                                        break;
                                }
                                break;
                            case 0xf0: // Four byte code
                                pExtChar = p;
                                p++;
                                switch (*pExtChar) {
                                    case 0x90:
                                        pExtChar = p;
                                        p++;
                                        switch (*pExtChar) {
                                            case 0x92: // Osage
                                                if ((*p >= 0xb0)
                                                    && (*p <= 0xbf)) {
                                                    *pExtChar = 0x93;
                                                    (*p) -= 0x18;
                                                }
                                                break;
                                            case 0x93: // Osage
                                                if ((*p >= 0x80)
                                                    && (*p <= 0x93))
                                                    (*p) += 0x18;
                                                break;
                                            default:
                                                break;
                                        }
                                        break;
                                    default:
                                        break;
                                }
                                break;
                            case 0x9E:
                                pExtChar = p;
                                p++;
                                switch (*pExtChar) {
                                    case 0xA4: // Adlam
                                        if ((*p >= 0x80)
                                            && (*p <= 0xA1))
                                            (*p) += 0x22;
                                        break;
                                    default:
                                        break;
                                }
                                break;
                            default:
                                break;
                        }
                        pExtChar = 0;
                    }
                    p++;
                }
            }
            return pString;
        }

        unsigned char *StringToUpperExt(unsigned char *pString) { // TODO: Refactor StringToUpperExt function;
            if (pString && *pString) {
                unsigned char *p = pString;
                unsigned char *pExtChar = 0;
                while (*p) {
                    if ((*p >= 0x61) && (*p <= 0x7a)) // US ASCII
                        (*p) -= 0x20;
                    else if (*p > 0xc0) {
                        pExtChar = p;
                        p++;
                        switch (*pExtChar) {
                            case 0xc3: // Latin 1
                                if ((*p >= 0xa0)
                                    && (*p <= 0xbe)
                                    && (*p != 0xb7))
                                    (*p) -= 0x20; // US ASCII shift
                                break;
                            case 0xc4: // Latin Exteneded
                                if ((*p >= 0x80)
                                    && (*p <= 0xb7)
                                    && (*p % 2)) // Odd
                                    (*p)--; // Prev char is upr
                                else if ((*p >= 0xb9)
                                         && (*p <= 0xbe)
                                         && (!(*p % 2))) // Even
                                    (*p)--; // Prev char is upr
                                else if (*p == 0xbf) {
                                    *pExtChar = 0xc5;
                                    (*p) = 0x80;
                                }
                                break;
                            case 0xc5: // Latin Exteneded
                                if ((*p >= 0x80)
                                    && (*p <= 0x88)
                                    && (!(*p % 2))) // Even
                                    (*p)--; // Prev char is upr
                                else if ((*p >= 0x8a)
                                         && (*p <= 0xb7)
                                         && (*p % 2)) // Odd
                                    (*p)--; // Prev char is upr
                                else if ((*p >= 0xb9)
                                         && (*p <= 0xbe)
                                         && (!(*p % 2))) // Even
                                    (*p)--; // Prev char is upr
                                break;
                            case 0xc6: // Latin Exteneded
                                switch (*p) {
                                    case 0x83:
                                    case 0x85:
                                    case 0x88:
                                    case 0x8c:
                                    case 0x92:
                                    case 0x99:
                                    case 0xa1:
                                    case 0xa3:
                                    case 0xa5:
                                    case 0xa8:
                                    case 0xad:
                                    case 0xb0:
                                    case 0xb4:
                                    case 0xb6:
                                    case 0xb9:
                                    case 0xbd:
                                        (*p)--; // Prev char is upr
                                        break;
                                    default:
                                        break;
                                }
                                break;
                            case 0xc7: // Latin Exteneded
                                if (*p == 0x86)
                                    (*p) = 0x84;
                                else if (*p == 0x85)
                                    (*p)--; // Prev char is upr
                                else if (*p == 0x89)
                                    (*p) = 0x87;
                                else if (*p == 0x88)
                                    (*p)--; // Prev char is upr
                                else if (*p == 0x8c)
                                    (*p) = 0x8a;
                                else if (*p == 0x8b)
                                    (*p)--; // Prev char is upr
                                else if ((*p >= 0x8d)
                                         && (*p <= 0x9c)
                                         && (!(*p % 2))) // Even
                                    (*p)--; // Prev char is upr
                                else if ((*p >= 0x9e)
                                         && (*p <= 0xaf)
                                         && (*p % 2)) // Odd
                                    (*p)--; // Prev char is upr
                                else if (*p == 0xb3)
                                    (*p) = 0xb1;
                                else if (*p == 0xb2)
                                    (*p)--; // Prev char is upr
                                else if (*p == 0xb4)
                                    (*p)--; // Prev char is upr
                                else if (*p == 0xb8)
                                    (*p)--; // Prev char is upr
                                else if (*p == 0xba)
                                    (*p)--; // Prev char is upr
                                else if (*p == 0xbc)
                                    (*p)--; // Prev char is upr
                                else if (*p == 0xbe)
                                    (*p)--; // Prev char is upr
                                break;
                            case 0xc8: // Latin Exteneded
                                if ((*p >= 0x80)
                                    && (*p <= 0x9f)
                                    && (*p % 2)) // Odd
                                    (*p)--; // Prev char is upr
                                else if ((*p >= 0xa2)
                                         && (*p <= 0xb3)
                                         && (*p % 2)) // Odd
                                    (*p)--; // Prev char is upr
                                else if (*p == 0xbc)
                                    (*p)--; // Prev char is upr
                                break;
                            case 0xcd: // Greek & Coptic
                                switch (*p) {
                                    case 0xb1:
                                    case 0xb3:
                                    case 0xb7:
                                        (*p)--; // Prev char is upr
                                        break;
                                    default:
                                        if (*p == 0xbb) {
                                            *pExtChar = 0xcf;
                                            (*p) = 0xbd;
                                        } else if (*p == 0xbc) {
                                            *pExtChar = 0xcf;
                                            (*p) = 0xbe;
                                        } else if (*p == 0xbd) {
                                            *pExtChar = 0xcf;
                                            (*p) = 0xbf;
                                        }
                                        break;
                                }
                                break;
                            case 0xce: // Greek & Coptic
                                if (*p == 0xac)
                                    (*p) = 0x86;
                                else if (*p == 0xad)
                                    (*p) = 0x88;
                                else if (*p == 0xae)
                                    (*p) = 0x89;
                                else if (*p == 0xaf)
                                    (*p) = 0x8a;
                                else if ((*p >= 0xb1)
                                         && (*p <= 0xbf))
                                    (*p) -= 0x20; // US ASCII shift
                                break;
                            case 0xcf: // Greek & Coptic
                                if (*p == 0xb4)
                                    (*p) = 0x8f;
                                else if (*p == 0x92)
                                    (*p)--; // Prev char is upr
                                else if ((*p >= 0x98)
                                         && (*p <= 0xaf)
                                         && (*p % 2)) // Odd
                                    (*p)--; // Prev char is upr
                                else if (*p == 0x91)
                                    (*p) = 0xb4;
                                else if (*p == 0xb8)
                                    (*p)--; // Prev char is upr
                                else if (*p == 0xb2)
                                    (*p) = 0xb9;
                                else if (*p == 0xbc)
                                    (*p)--; // Prev char is upr
                                else if (*p == 0x8c) {
                                    *pExtChar = 0xce;
                                    (*p) = 0x8c;
                                } else if (*p == 0x8d) {
                                    *pExtChar = 0xce;
                                    (*p) = 0x8e;
                                } else if (*p == 0x8e) {
                                    *pExtChar = 0xce;
                                    (*p) = 0x8f;
                                } else if ((*p >= 0x80)
                                           && (*p <= 0x8b)
                                           && (*p != 0x82)) {
                                    *pExtChar = 0xce;
                                    (*p) += 0x20;
                                } else if (*p == 0xb3) {
                                    *pExtChar = 0xcd;
                                    (*p) = 0xbf;
                                }
                                break;
                            case 0xd0: // Cyrillic
                                if ((*p >= 0xb0)
                                    && (*p <= 0xbf))
                                    (*p) -= 0x20; // US ASCII shift
                                break;
                            case 0xd1: // Cyrillic supplement
                                if ((*p >= 0x90)
                                    && (*p <= 0x9f)) {
                                    *pExtChar = 0xd0;
                                    (*p) -= 0x10;
                                } else if ((*p >= 0x80)
                                           && (*p <= 0x8f)) {
                                    *pExtChar = 0xd0;
                                    (*p) += 0x20;
                                } else if ((*p >= 0xa0)
                                           && (*p <= 0xbf)
                                           && (*p % 2)) // Odd
                                    (*p)--; // Prev char is upr
                                break;
                            case 0xd2: // Cyrillic supplement
                                if (*p == 0x80)
                                    (*p)++; // Prev char is upr
                                else if ((*p >= 0x8a)
                                         && (*p <= 0xbf)
                                         && (*p % 2)) // Odd
                                    (*p)--; // Prev char is upr
                                break;
                            case 0xd3: // Cyrillic supplement
                                if ((*p >= 0x81)
                                    && (*p <= 0x8e)
                                    && (!(*p % 2))) // Even
                                    (*p)--; // Prev char is upr
                                else if ((*p >= 0x90)
                                         && (*p <= 0xbf)
                                         && (*p % 2)) // Odd
                                    (*p)--; // Prev char is upr
                                break;
                            case 0xd4: // Cyrillic supplement & Armenian
                                if ((*p >= 0x80)
                                    && (*p <= 0xaf)
                                    && (*p % 2)) // Odd
                                    (*p)--; // Prev char is upr
                                break;
                            case 0xd5: // Armenian
                                if ((*p >= 0x80)
                                    && (*p <= 0x96)
                                    && (*p % 2)) // Odd
                                    (*p)--; // Prev char is upr
                                else if ((*p >= 0xa1)
                                         && (*p <= 0xaf)) {
                                    *pExtChar = 0xd4;
                                    (*p) += 0x10;
                                }
                                break;
                            case 0xe1: // Three byte code
                                pExtChar = p;
                                p++;
                                switch (*pExtChar) {
                                    case 0x82: // Georgian
                                        break;
                                    case 0x83: // Georgian
                                        if ((*p >= 0x90)
                                            && (*p <= 0xaf)) {
                                            *pExtChar = 0x82;
                                            (*p) += 0x10;
                                        } else if ((*p >= 0xb0)
                                                   && ((*p <= 0xb5)
                                                       || (*p == 0xb7))
                                                   || (*p == 0xbd))
                                            (*p) -= 0x30;
                                        break;
                                    case 0xb8: // Latin extened
                                        if ((*p >= 0x80)
                                            && (*p <= 0xbf)
                                            && (*p % 2)) // Odd
                                            (*p)--; // Prev char is upr
                                        break;
                                    case 0xb9: // Latin extened
                                        if ((*p >= 0x80)
                                            && (*p <= 0xbf)
                                            && (*p % 2)) // Odd
                                            (*p)--; // Prev char is upr
                                        break;
                                    case 0xba: // Latin extened
                                        if ((*p >= 0x80)
                                            && (*p <= 0x94)
                                            && (*p % 2)) // Odd
                                            (*p)--; // Prev char is upr
                                        else if ((*p >= 0x9e)
                                                 && (*p <= 0xbf)
                                                 && (*p % 2)) // Odd
                                            (*p)--; // Prev char is upr
                                        break;
                                    case 0xbb: // Latin extened
                                        if ((*p >= 0x80)
                                            && (*p <= 0xbf)
                                            && (*p % 2)) // Odd
                                            (*p)--; // Prev char is upr
                                        break;
                                    case 0xbc: // Greek extened
                                        if ((*p >= 0x80)
                                            && (*p <= 0x87))
                                            (*p) += 0x08;
                                        else if ((*p >= 0x90)
                                                 && (*p <= 0x97))
                                            (*p) += 0x08;
                                        else if ((*p >= 0xa0)
                                                 && (*p <= 0xa7))
                                            (*p) += 0x08;
                                        else if ((*p >= 0xb0)
                                                 && (*p <= 0x87))
                                            (*p) += 0x08;
                                        break;
                                    case 0xbd: // Greek extened
                                        if ((*p >= 0x80)
                                            && (*p <= 0x87))
                                            (*p) += 0x08;
                                        else if ((*p >= 0x90)
                                                 && (*p <= 0x97))
                                            (*p) += 0x08;
                                        else if ((*p >= 0xa0)
                                                 && (*p <= 0xa7))
                                            (*p) += 0x08;
                                        else if ((*p >= 0xb0)
                                                 && (*p <= 0x87))
                                            (*p) += 0x08;
                                        break;
                                    case 0xbe: // Greek extened
                                        if ((*p >= 0x80)
                                            && (*p <= 0x87))
                                            (*p) += 0x08;
                                        else if ((*p >= 0x90)
                                                 && (*p <= 0x97))
                                            (*p) += 0x08;
                                        else if ((*p >= 0xa0)
                                                 && (*p <= 0xa7))
                                            (*p) += 0x08;
                                        else if ((*p >= 0xb0)
                                                 && (*p <= 0xb1))
                                            (*p) += 0x08;
                                        break;
                                    case 0xbf: // Greek extened
                                        if ((*p >= 0x80)
                                            && (*p <= 0x84))
                                            (*p) += 0x08;
                                        else if ((*p >= 0x90)
                                                 && (*p <= 0x93))
                                            (*p) += 0x08;
                                        else if ((*p >= 0xa0)
                                                 && (*p <= 0xa4))
                                            (*p) += 0x08;
                                        break;
                                    default:
                                        break;
                                }
                                break;
                            case 0xf0: // Four byte code
                                pExtChar = p;
                                p++;
                                switch (*pExtChar) {
                                    case 0x90:
                                        pExtChar = p;
                                        p++;
                                        switch (*pExtChar) {
                                            case 0x92: // Osage
                                                break;
                                            case 0x93: // Osage
                                                if ((*p >= 0x80)
                                                    && (*p <= 0x93))
                                                    (*p) += 0x18;
                                                else if ((*p >= 0x98)
                                                         && (*p <= 0xa7)) {
                                                    *pExtChar = 0x92;
                                                    (*p) += 0x18;
                                                }
                                                break;
                                            default:
                                                break;
                                        }
                                        break;
                                    case 0x9E:
                                        pExtChar = p;
                                        p++;
                                        switch (*pExtChar) {
                                            case 0xA4: // Adlam
                                                if ((*p >= 0xa2)
                                                    && (*p <= 0xc3))
                                                    (*p) -= 0x22;
                                                break;
                                            default:
                                                break;
                                        }
                                        break;
                                    default:
                                        break;
                                }
                                break;
                            default:
                                break;
                        }
                        pExtChar = 0;
                    }
                    p++;
                }
            }
            return pString;
        }

    }
}