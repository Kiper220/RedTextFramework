#include <RTF.h>
#include <iostream>
#include <RTD/Memory/Allocator.h>
#include <vector>
#ifdef WIN32
#include <Windows.h>
#endif
extern "C"{
    #include <dlfcn.h>
};


class T{
public:
    T(){
        std::cout << "construct\n";
        i = 1953719668;
        c++;
    }
    void operator=(const T& t){
        this->i = t.i;
    }
    ~T(){
        std::cout << "destruct\n";
        if(i != 1953719668)
            err = true;
        c--;
    }
    int i = 1953719668;
    static bool err;
    static int c;
};
class S{
public:
    T t;
};


int T::c = 0;
bool T::err = false;


using namespace std;


int main() {
#ifdef WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    {
        RTF::Memory::BasicAllocator<S> test;
        std::vector<S> test2;
        for(size_t i = 0; i < 1; i++){
            test.Allocate(1);
            test.Allocate(2);
            test.Insert(test.begin(), S());
            test.Allocate(2);
            test.Allocate(0);
            test.Allocate(0);
            test.Allocate(0);
            test.Allocate(1);
        }
    }
    std::cout << T::c << '\n';

    if(RTF::Tests::RunAllTestAndLog())
        if(!T::err && !T::c){
            std::cout << "Allocator Test >> OK;\n";
            return 0;
        }
    return 1;
}
