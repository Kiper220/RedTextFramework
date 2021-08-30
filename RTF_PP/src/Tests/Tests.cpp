//
// Created by kiper220 on 14.08.2021.
//

#include <Tests/RTF/Tests.h>
#include <RTD/Memory/SharedPointer.h>
#include <RTD/Memory/ASharedPointer.h>
#include <RTD/Strings/SharedString.h>
#include <RTD/Memory/Allocator.h>
#include <RTD/Strings/BasicUTF8String.h>
#include <iostream>

namespace RTF{
    namespace Tests{
        Containers::Pair<bool,Containers::Pair<char,char>> RunAllTest(){
#ifdef TESTS_ON
            for(int i = 0; i < 100; i++){
                if(!TEST(RTD,Strings,BasicUtf8String)())
                    return {false, {_RTD, UnderModule::_RTD_STRINGS}};

                if(!TEST(RTD,Types,ASharedPointer)())
                    return {false, {_RTD, UnderModule::_RTD_TYPES}};

                if(!TEST(RTD,Types,SharedPointer)())
                    return {false, {_RTD, UnderModule::_RTD_TYPES}};

                if(!TEST(RTD,Strings,SharedString)())
                    return {false, {_RTD, UnderModule::_RTD_STRINGS}};

                if(!TEST(RTD,Memory,BasicAllocator)())
                    return {false, {_RTD, UnderModule::_RTD_MEMORY}};
            }
#endif
return {true, {_NONE, UnderModule::_RTD_NONE}};
        }
        bool RunAllTestAndLog(){
            auto allTestResoult = RTF::Tests::RunAllTest();
#ifdef TESTS_ON
            if(!allTestResoult.first){
                std::cout << "TESTS ERROR:\n";
                switch ((RTF::Tests::Module)allTestResoult.second.first) {
                    case RTF::Tests::_NONE:
                        break;
                    case RTF::Tests::_APPLICATION: {
                        std::cout << "\tMODULE ERROR: Application;\n";

                        switch ((RTF::Tests::UnderModule::APPLICATION_Modules_Type)allTestResoult.second.second) {
                            case RTF::Tests::UnderModule::_APPLICATION_NONE:
                                break;

                            case RTF::Tests::UnderModule::_APPLICATION_GAME_APPLICATION:
                                std::cout << "\tUNDERMODULE ERROR: GameApplication;\n";
                                break;

                                case RTF::Tests::UnderModule::_APPLICATION_WIDGET_APPLICATION:
                                    std::cout << "\tUNDERMODULE ERROR: WidgetApplication;\n";
                                    break;
                        }
                        break;
                    }
                    case RTF::Tests::_DATA_COLLECT:{
                        std::cout << "\tMODULE ERROR: DataCollect;\n";

                        switch ((RTF::Tests::UnderModule::DATA_Modules_Type)allTestResoult.second.second) {
                            case RTF::Tests::UnderModule::_DATA_NONE:
                                break;
                            case RTF::Tests::UnderModule::_DATA_COLLECT_DB:
                                std::cout << "\tUNDERMODULE ERROR: DB;\n";
                                break;
                                case RTF::Tests::UnderModule::_DATA_COLLECT_INI:
                                    std::cout << "\tUNDERMODULE ERROR: INI;\n";
                                    break;
                                    case RTF::Tests::UnderModule::_DATA_COLLECT_JSON:
                                        std::cout << "\tUNDERMODULE ERROR: JSON;\n";
                                        break;
                        }
                        break;
                    }
                    case RTF::Tests::_PLATFORM: {
                        std::cout << "\tMODULE ERROR: Platform;\n";

                        switch ((RTF::Tests::UnderModule::PLATFORM_Modules_Type)allTestResoult.second.second) {
                            case RTF::Tests::UnderModule::_PLATFORM_NONE:
                                break;
                            case RTF::Tests::UnderModule::_PLATFORM_GRAPHICS:
                                std::cout << "\tUNDERMODULE ERROR: Graphics;\n";
                                break;
                                case RTF::Tests::UnderModule::_PLATFORM_INPUT:
                                    std::cout << "\tUNDERMODULE ERROR: Input;\n";
                                    break;
                                    case RTF::Tests::UnderModule::_PLATFORM_MULTIMEDIA:
                                        std::cout << "\tUNDERMODULE ERROR: Multimedia;\n";
                                        break;
                                        case RTF::Tests::UnderModule::_PLATFORM_NETWORK:
                                            std::cout << "\tUNDERMODULE ERROR: Network;\n";
                                            break;
                                            case RTF::Tests::UnderModule::_PLATFORM_SYSTEM:
                                                std::cout << "\tUNDERMODULE ERROR: System;\n";
                                                break;
                                                case RTF::Tests::UnderModule::_PLATFORM_UI:
                                                    std::cout << "\tUNDERMODULE ERROR: UI;\n";
                                                    break;
                        }
                        break;
                    }
                    case RTF::Tests::_RTD: {
                        std::cout << "\tMODULE ERROR: RTD;\n";

                        switch ((RTF::Tests::UnderModule::RTD_Modules_Type)allTestResoult.second.second) {
                            case RTF::Tests::UnderModule::_RTD_NONE:
                                break;
                            case RTF::Tests::UnderModule::_RTD_CONTAINERS:
                                std::cout << "\tUNDERMODULE ERROR: Containers;\n";
                                break;
                                case RTF::Tests::UnderModule::_RTD_EVENTS:
                                    std::cout << "\tUNDERMODULE ERROR: Events;\n";
                                    break;
                                    case RTF::Tests::UnderModule::_RTD_EXCEPTIONS:
                                        std::cout << "\tUNDERMODULE ERROR: Exceptions;\n";
                                        break;
                                        case RTF::Tests::UnderModule::_RTD_GRAPHICS:
                                            std::cout << "\tUNDERMODULE ERROR: Graphics;\n";
                                            break;
                                            case RTF::Tests::UnderModule::_RTD_MATH:
                                                std::cout << "\tUNDERMODULE ERROR: Math;\n";
                                                break;
                                                case RTF::Tests::UnderModule::_RTD_PATTERNS:
                                                    std::cout << "\tUNDERMODULE ERROR: Patterns;\n";
                                                    break;
                                                    case RTF::Tests::UnderModule::_RTD_STRINGS:
                                                        std::cout << "\tUNDERMODULE ERROR: Strings;\n";
                                                        break;
                                                        case RTF::Tests::UnderModule::_RTD_TYPES:
                                                            std::cout << "\tUNDERMODULE ERROR: Types;\n";
                                                            break;
                                                            case RTF::Tests::UnderModule::_RTD_MEMORY:
                                                                std::cout << "\tUNDERMODULE ERROR: Memory;\n";
                                                                break;
                        }
                        break;
                    }
                    case RTF::Tests::_WIDGETS: {
                        std::cout << "\tMODULE ERROR: Widget;\n";

                        switch ((RTF::Tests::UnderModule::WIDGET_Modules_Type)allTestResoult.second.second) {
                            case RTF::Tests::UnderModule::_WIDGET_NONE:
                                break;
                            case RTF::Tests::UnderModule::_WIDGET_DYNAMIC:
                                std::cout << "\tUNDERMODULE ERROR: Dynamic;\n";
                                break;
                                case RTF::Tests::UnderModule::_WIDGET_STATIC:
                                    std::cout << "\tUNDERMODULE ERROR: Static;\n";
                                    break;
                        }
                        break;
                    }
                }
            }
            else{
#endif
                std::cout << "All Tests >> OK;\n";
                return true;
#if TESTS_ON
            }
            return false;
#endif
        }
    }
}