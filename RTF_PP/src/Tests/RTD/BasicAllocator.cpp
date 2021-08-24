//
// Created by kiper220 on 24.08.2021.
//
#include <Tests/RTF/Tests.h>
#include <RTD/Memory/Allocator.h>

class T{
public:
    T(){
        i = 1953719668;
        c++;
    }
    void operator=(const T& t){
        this->i = t.i;

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
class S{
public:
    T t;
};


int T::c = 0;
bool T::err = false;

namespace RTF{
    bool TEST(RTD, Memory, BasicAllocator)(){     /// warning: see the memory leak

        try{
            RTF::Memory::BasicAllocator<S> test;
            for(size_t i = 0; i < 100; i++){
                test.Allocate(1648);
                test.Allocate(128);
                test.Insert(test.begin(), S());
                test.Allocate(98);
                test.Insert(test.end(), S());
                test.Allocate(1750);
                test.Insert(test.begin() + 879, S());
                test.Allocate(2648);
                test.Insert(test.end() - 1458, S());
                test.Allocate(512);
                test.Allocate(28);
            }
        }
        catch(...){
            return false;
        }
        if(!T::err && !T::c)
            return true;
        return false;
    }

}