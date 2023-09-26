#pragma once

#include "ICommandLogger.h"

#include <string>

namespace Bulk
{
    class FCmdCommandLogger : public ICommandLogger
    {
    public:
        virtual void Log(const std::string& str) override;
    };
}