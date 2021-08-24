//
// Created by kiper220 on 14.08.2021.
//

#ifndef REDTEXTAPPLICATION_TESTS_H
#define REDTEXTAPPLICATION_TESTS_H
#include <RTD/Types/Pair.h>


namespace RTF{
    namespace Tests{
        enum Module : char{
            _NONE = 0,
            _APPLICATION,
            _DATA_COLLECT,
            _PLATFORM,
            _RTD,
            _WIDGETS
        };
        union UnderModule{
            enum APPLICATION_Modules_Type: char{
                _APPLICATION_NONE = 0,
                _APPLICATION_GAME_APPLICATION,
                _APPLICATION_WIDGET_APPLICATION
            } APPLICATION_Modules;
            enum DATA_Modules_Type : char{
                _DATA_NONE = 0,
                _DATA_COLLECT_DB,
                _DATA_COLLECT_INI,
                _DATA_COLLECT_JSON
            } DATA_COLLECT_Modules;
            enum PLATFORM_Modules_Type: char{
                _PLATFORM_NONE = 0,
                _PLATFORM_GRAPHICS,
                _PLATFORM_INPUT,
                _PLATFORM_MULTIMEDIA,
                _PLATFORM_NETWORK,
                _PLATFORM_SYSTEM,
                _PLATFORM_UI,
            } PLATFORM_Modules;
            enum RTD_Modules_Type : char{
                _RTD_NONE = 0,
                _RTD_CONTAINERS,
                _RTD_EVENTS,
                _RTD_EXCEPTIONS,
                _RTD_GRAPHICS,
                _RTD_MATH,
                _RTD_PATTERNS,
                _RTD_STRINGS,
                _RTD_TYPES,
                _RTD_MEMORY
            } RTD_Modules;
            enum WIDGET_Modules_Type : char{
                _WIDGET_NONE = 0,
                _WIDGET_DYNAMIC,
                _WIDGET_STATIC,
            } WIDGET_Modules;
        };
        Containers::Pair<bool,Containers::Pair<char,char>> RunAllTest();
        bool RunAllTestAndLog();
#ifdef TESTS_ON
#define TEST(_MODULE, _UNDERMODULE, _TESTNAME) \
_MODULE ## _UNDERMODULE ## _TESTNAME
#endif

    }
}


#endif //REDTEXTAPPLICATION_TESTS_H
