#include <RTF.h>
#include <iostream>
#include <RTD/Memory/Allocator.h>
#ifdef WIN32
#include <Windows.h>
#endif

class T{
public:
    T(){
        std::cout << "construct\n";
    }
    ~T(){
        std::cout << "destruct\n";
    }

};

using namespace std;


int main() {
#ifdef WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    RTF::Memory::BasicStackAllocator<T> test;
    test.Allocate(5);
    test.Allocate(2);
    test.Allocate(3);
    test.Allocate(6);

    if(RTF::Tests::RunAllTestAndLog())
        return 0;
    return 1;
}
