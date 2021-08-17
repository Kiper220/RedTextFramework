//
// Created by kiper220 on 22.07.2021.
//

#ifndef REDTEXTAPPLICATION_EVENT_H
#define REDTEXTAPPLICATION_EVENT_H

namespace RTF{
    namespace Events{

        template<typename EventDataType>
        class Event;
        class KeyboardEvent;        //TODO : Write KeyboardEvent class;
        class MouseEvent;           //TODO : Write MouseEvent class;
        class WindowEvent;          //TODO : Write WindowEvent class;
        class JoystickEvent;        //TODO : Write JoystickEvent class;
        class SystemEvent;          //TODO : Write SystemEvent class;
        class TimeEvent;            //TODO : Write TimeEvent class;
    }
}

#endif //REDTEXTAPPLICATION_EVENT_H
