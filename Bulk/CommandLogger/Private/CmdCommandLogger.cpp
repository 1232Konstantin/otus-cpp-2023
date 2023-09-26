#include "CmdCommandLogger.h"

#include <memory>

using namespace Bulk;

std::shared_ptr<ICommandLogger> CommandLoggerFactory::Create()
{
    return std::make_shared<FCmdCommandLogger>();
}

void FCmdCommandLogger::Log(const std::string& str)
{
    // TODO print to cmd
}