//
// Created by kiper220 on 22.07.2021.
//

#ifndef REDTEXTAPPLICATION_EVENT_H
#define REDTEXTAPPLICATION_EVENT_H

#include <Implementation/RTD/Containers/SharedVector.h>

namespace RTF{
    namespace Events{

        template<typename EventDataType>
        class Event{                                                                //TODO: Refactor and write Event class(and src)
        public:
            typedef Types::Vector<void(*)(EventDataType)> EventListType;

        public:

            Event() = default;
            Event(const Event &event) = default;

            virtual void CallEvent(EventDataType eventData) const = 0;

            virtual EventListType& GetReferenceEventList() = 0;
            virtual EventListType GetEventList() const = 0;

            virtual void SetEventList(const EventListType &eventListType) = 0;

            virtual Event& operator=(const Event &event) = 0;

            virtual ~Event() = 0;

        };
    }
}

#endif //REDTEXTAPPLICATION_EVENT_H
