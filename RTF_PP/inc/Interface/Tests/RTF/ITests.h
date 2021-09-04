//
// Created by kiper220 on 14.08.2021.
//

#ifndef REDTEXTAPPLICATION_TESTS_H
#define REDTEXTAPPLICATION_TESTS_H
#include <RTD/Types/Pair.h>


namespace RTF{
    namespace Tests{
        Containers::Pair<bool,Containers::Pair<char,char>> RunAllTest();
        bool RunAllTestAndLog();
    }
}


#endif //REDTEXTAPPLICATION_TESTS_H
