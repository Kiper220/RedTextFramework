//
// Created by kiper220 on 14.08.2021.
//
#include <Tests/RTF/Tests.h>
#include <RTD/Memory/SharedPointer.h>

namespace RTF{
    bool TEST(RTD, Types, SharedPointer)(){     /// warning: see the memory leak

        Types::SharedPointer<int> pointer1 = (int*)nullptr, pointer2 = (int*)nullptr, pointer3;
        {
            Types::SharedPointer<int> sharedPointer = new int;
            *sharedPointer = 5;
            if(++*sharedPointer != 6)
                return false;

            {
                Types::SharedPointer<int> tmp = new int;
                *tmp = 4;
                pointer2 = tmp;
                sharedPointer = tmp;
            }

            if(++*sharedPointer != 5)
                return false;

            pointer1 = sharedPointer;

            sharedPointer.DestructThis();

            if(sharedPointer != nullptr){
                return false;
            }
        }
        pointer3 = pointer2;
        pointer3 = pointer1;
        if(*pointer3 != *pointer2)
            return false;

        return true;
    }

}