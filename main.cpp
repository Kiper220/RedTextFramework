#include <RTF.h>
#ifdef WIN32
#include <Windows.h>
#endif

using namespace std;


int main() { // TODO: Fix for Windows
#ifdef WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    if(RTF::Tests::RunAllTestAndLog())
        return 0;
    return 1;
}
