//
// Created by kiper220 on 22.07.2021.
//

#include <Implementation/RTD/Exceptions/Exception.h>

namespace RTF{
    namespace Exceptions{
        Exception::Exception() noexcept = default;
        Exception::Exception(const Exception& exception) noexcept = default;
    }
}
