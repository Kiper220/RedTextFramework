//
// Created by kiper220 on 14.06.2021.
//
#include <Interface/RTD/Graphics/IImage.h>
#include <Interface/RTD/Math/IVector.h>

#ifndef REDTEXTAPPLICATION_IWINDOW_H
#define REDTEXTAPPLICATION_IWINDOW_H

namespace RTF{
    class IWindow {
    public:
        IWindow(RTD::IImage8 Icon, std::string Title,
                Types::IVector2 size, Types::IVector2 position);


    };
}

#endif //REDTEXTAPPLICATION_IWINDOW_H
