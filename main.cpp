#include <RTF.h>
#include <iostream>
#include <Windows.h>

int main() {
#ifdef WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    if(RTF::Tests::RunAllTestAndLog())
        return 0;
    return 1;
}
