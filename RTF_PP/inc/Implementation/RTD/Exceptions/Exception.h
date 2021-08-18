//
// Created by kiper220 on 22.07.2021.
//

#ifndef REDTEXTAPPLICATION_EXCEPTION_H
#define REDTEXTAPPLICATION_EXCEPTION_H
#include <RTD/Strings/SharedString.h>

namespace RTF{
    namespace Exceptions{
        class IException{
        public:
            IException() noexcept;
            IException(const IException& exception) noexcept;

            virtual Strings::SharedString What() = 0;

            virtual ~IException() = 0;
        };
    }
}

#endif //REDTEXTAPPLICATION_EXCEPTION_H
