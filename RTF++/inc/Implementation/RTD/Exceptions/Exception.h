//
// Created by kiper220 on 22.07.2021.
//

#ifndef REDTEXTAPPLICATION_EXCEPTION_H
#define REDTEXTAPPLICATION_EXCEPTION_H
#include <Implementation/RTD/Strings/String.h>

namespace RTF{
    namespace Exceptions{
        class Exception{
        public:
            Exception() noexcept;
            Exception(const Exception& exception) noexcept;

            virtual Strings::String What() = 0;

            virtual ~Exception() = 0;
        };
    }
}

#endif //REDTEXTAPPLICATION_EXCEPTION_H
