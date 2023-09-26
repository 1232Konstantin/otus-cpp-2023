#pragma once

#include "ICommandReceiver.h"

namespace Bulk
{
    class FCmdCommandReceiver : public ICommandReceiver
    {
    public:

        explicit FCmdCommandReceiver(const OnCommandReceived& inCommandReceivedCallback);

        virtual bool Begin() override;
    };
}