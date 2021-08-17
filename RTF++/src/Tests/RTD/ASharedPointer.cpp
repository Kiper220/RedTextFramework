//
// Created by kiper220 on 14.08.2021.
//
#include <RTF/Tests.h>
#include <RTD/Memory/ASharedPointer.h>


namespace RTF{
    bool TEST(RTD, Types, ASharedPointer)(){     /// warning: see the memory leak
        Types::ASharedPointer<int> pointer1 = (int*)nullptr, pointer2 = (int*)nullptr, pointer3;
        {
            Types::ASharedPointer<int> sharedPointer = new int[2];
            sharedPointer[1] = 5;
            if(++sharedPointer[1] != 6)
                return false;

            {
                Types::ASharedPointer<int> tmp = new int[2];
                tmp[0] = 4;
                pointer2 = tmp;
                sharedPointer = tmp;
            }

            if(++sharedPointer[0] != 5)
                return false;

            pointer1 = sharedPointer;

            sharedPointer.DestructThis();

            if(sharedPointer != nullptr){
                return false;
            }
        }
        pointer3 = pointer2;
        pointer3 = pointer1;
        if(pointer3[1] != pointer2[1])
            return false;

        return true;
    }
}