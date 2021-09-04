//
// Created by kiper220 on 30.08.2021.
//
#include <RTF/Tests.h>
#include <RTD/Strings/BasicUTF8String.h>
#ifdef TESTS_ON
namespace RTF{
    bool TEST(RTD, Strings, BasicUtf8String)(){
        RTF::Strings::BasicUtf8String<char> string1 = "Test", string2 = "1", string3 = "\n", string4;

        for(auto s = 0; s < 5000; s++){
            string4 = string1 + string2 + string3;
        }
        string1 = string4;

        if(string1 != string4 || string1 != "Test1\n")
            return false;

        string1.ToUpper();
        string4.ToUpper();

        if(string1 != string4 || string1 != "TEST1\n")
            return false;

        string1.ToLower();
        string4.ToLower();

        if(string1 != string4 || string1 != "test1\n")
            return false;

        return true;
    }
}
#endif