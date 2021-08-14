//
// Created by kiper220 on 22.07.2021.
//

#include <RTD/Exceptions/Exception.h>

namespace RTF{
    namespace Exceptions{
        IException::IException() noexcept = default;
        IException::IException(const IException& exception) noexcept = default;
    }
}
