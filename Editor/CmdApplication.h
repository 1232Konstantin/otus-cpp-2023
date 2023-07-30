#pragma once
#include <iostream>
#include <memory>
#include <sstream>

#include "IStorage.h"
#include "IInputController.h"
#include "IGUI.h"

namespace Editor
{
    class FCmdApplication
    {
    public:

        explicit FCmdApplication(std::istream& in = std::cin);
        bool Begin();
        bool EventLoop();

    private:

        bool HandleInput();

        std::istream& Stream;
        bool IsRunning = true;

        std::shared_ptr<IGUI> Gui;
        std::shared_ptr<IStorage> Storage;
        std::shared_ptr<IInputController> InputController;
    };
}
