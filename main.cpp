#include <RTF.h>
#include <RTD/Containers/Vector.h>
#include <iostream>
#include <Platform/System/Windows/IWindow.h>
#include <RTD/Strings/String.h>
#include <time.h>
#ifdef WIN32
#include <Windows.h>
#endif

using namespace std;


int main() { // TODO: Fix for Windows
#ifdef WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    RTF::Strings::BasicUtf8String<char> string1 = "Test", string2 = "1", string3 = "\n", string4;

    for(auto s = 0; s < 50000000; s++){
        string4 = string1 + string2 + string3;
    }
    string1 = string4;

    if(string1 != string4 || string1 != "Test1\n"){
        std::cout << "Error\n";
    }


    if(RTF::Tests::RunAllTestAndLog())
        return 0;
    return 1;
}
