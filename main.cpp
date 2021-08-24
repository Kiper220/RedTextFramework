#include <RTF.h>
#include <iostream>
#include <RTD/Memory/Allocator.h>
#ifdef WIN32
#include <Windows.h>
#endif

using namespace std;


int main() {
#ifdef WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    if(RTF::Tests::RunAllTestAndLog())
            return 0;
    return 1;
}
