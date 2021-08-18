#include <RTF.h>
#include <iostream>
#include <RTD/Memory/Allocator.h>
#ifdef WIN32
#include <Windows.h>
#endif

class T{
public:
    T(){
        i = 1953719668;
        c++;
    }
    ~T(){
        if(i != 1953719668)
            err = true;
        c--;
    }
    int i = 1953719668;
    static bool err;
    static int c;
};

int T::c = 0;
bool T::err = false;

using namespace std;


int main() {
#ifdef WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    {
        RTF::Memory::BasicAllocator<T> test;
        test.Allocate(5);
        test.Allocate(2);
        test.Allocate(3);
        test.Allocate(512);
        test.Allocate(255);
    }

    if(RTF::Tests::RunAllTestAndLog())
        if(!T::err && !T::c){
            std::cout << "Allocator Test >> OK;\n";
            return 0;
        }
    return 1;
}
