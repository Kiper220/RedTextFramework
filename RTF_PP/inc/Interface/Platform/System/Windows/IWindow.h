//
// Created by kiper220 on 25.08.2021.
//

#ifndef CMAKE_INSTALL_CMAKE_IWINDOW_H
#define CMAKE_INSTALL_CMAKE_IWINDOW_H
#include <RTD/Memory/SharedPointer.h>
#include <RTD/Strings/SharedString.h>
#include <RTD/Math/Vector.h>

#include <utility>

namespace RTF{
    namespace Windows{
        enum GraphicsContext{
            DirectX11,
            DirectX12,
            OpenGL,
            OpenGLES,
            Vulkan,
        };
        enum WindowEvent{
            KeyEvent,
            MouseEvent,
            WindowCloseEvent,
            WindowResizeEvent,
            WindowMoveEvent,
            NONE,
        };

        class IWindow{
        public:
            IWindow() = default;
            explicit IWindow(   int32_t winPosX = 0,
                                int32_t winPosY = 0,
                                int32_t winSizeX = 720,
                                int32_t winSizeY = 280,
                                Strings::SharedString winName = "Empty Window",
                                GraphicsContext graphicsContext = Vulkan):
                                windowPositionX(winPosX),
                                windowPositionY(winPosY),
                                windowSizeX(winSizeX),
                                windowSizeY(winSizeY),
                                windowName(std::move(winName)),
                                graphicsContext(graphicsContext)
                                {}
            void SetWindowPositionX(int32_t winPositionX){
                this->windowPositionX = winPositionX;
            }
            void SetWindowPositionY(int32_t winPositionY){
                this->windowPositionY = winPositionY;
            }

            void SetWindowSizeX(uint32_t winSizeX){
                this->windowSizeX = winSizeX;
            }
            void SetWindowSizeY(uint32_t winSizeY){
                this->windowSizeY = winSizeY;
            }

            void SetWindowName(Strings::SharedString winName){
                this->windowName = winName;
            }

            virtual void CreateWindow() = 0;
            virtual void ShowWindow(bool visibility = true) = 0;
            virtual void CloseWindow() = 0;

            virtual Types::SharedPointer<IWindow> CreateChildWindow(    int32_t winPosX = 0,
                                                                        int32_t winPosY = 0,
                                                                        int32_t winSizeX = 720,
                                                                        int32_t winSizeY = 280,
                                                                        Strings::SharedString winName = "Empty Window",
                                                                        GraphicsContext graphicsContext = Vulkan) = 0;

            virtual Containers::SharedVector<Types::SharedPointer<IWindow>>& GetChildWindows() = 0;

            virtual Containers::Pair<WindowEvent, uint32_t> GetEvent() = 0; // TODO, Make event class.
            virtual Math::IVector2 GetMousePosition() = 0;
            virtual Math::IVector2 GetWindowPosition() = 0;
            virtual Math::IVector2 GetWindowSize() = 0;
            virtual GraphicsContext GetGraphicsContext() = 0;

        private:
            int32_t windowPositionX = 0;
            int32_t windowPositionY = 0;

            uint32_t windowSizeX = 0;
            uint32_t windowSizeY = 0;

            bool windowVisibility = false;

            Strings::SharedString windowName = "";

            Types::SharedPointer<IWindow> rootWindow;
            Containers::SharedVector<Types::SharedPointer<IWindow>> childWindows;

            const GraphicsContext graphicsContext = Vulkan;
        };
    }
}

#endif //CMAKE_INSTALL_CMAKE_IWINDOW_H
