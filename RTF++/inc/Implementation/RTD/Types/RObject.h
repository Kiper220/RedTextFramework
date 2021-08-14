//
// Created by kiper220 on 23.07.2021.
//

#ifndef REDTEXTAPPLICATION_ROBJECT_H
#define REDTEXTAPPLICATION_ROBJECT_H

#include <RTD/Strings/SharedString.h>
#include <RTD/Types/SharedPointer.h>

namespace RTF{
    namespace Types{
        class RObject{
        public:
            RObject();


        private:
            SharedPointer<RObject> parentObject;

            Container::SharedVector<RObject*> childrenObject;
            Container::SharedVector<RObject> objectsEvents;

            Strings::SharedString objectName;
        };
    }
}

#endif //REDTEXTAPPLICATION_ROBJECT_H
