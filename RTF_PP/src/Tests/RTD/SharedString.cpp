//
// Created by kiper220 on 24.08.2021.
//

#ifdef TESTS_ON
#include <RTF/Tests.h>
#include <RTD/Strings/SharedString.h>

namespace RTF{
    bool TEST(RTD, Strings, SharedString)(){
        try{
            Strings::SharedString string1 = "HelO, WoRld! ПриВЕт, мИр!", string2 = "hELo, wOrLD! пРИвеТ, МиР!", string3 = "Hello, World! Привет, Мир!";
            Strings::SharedString string4, string5, string6;

            string4 = string1, string4.ToUpper();
            string6 = string2, string6.ToUpper();

            if(string4 != string6)
                return false;
            string5 = string6;

            if(string5 != string4)
                return false;

            string5[5] = 't';

            if(string4 != string6)
                return false;

            string4 += string5;
            string6 += string5;

            if(string4 != string6)
                return false;
        }
        catch(...){
            return false;
        }

        return true;
    }
}
#endif