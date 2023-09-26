#include "CmdCommandReceiver.h"

#include <memory>

using namespace Bulk;

std::shared_ptr<ICommandReceiver> CommandReceiverFactory::Create(const OnCommandReceived& inCommandReceivedCallback)
{
    return std::make_shared<FCmdCommandReceiver>();
}

FCmdCommandReceiver::FCmdCommandReceiver(const OnCommandReceived& inCommandReceivedCallback)
    : ICommandReceiver(inCommandReceivedCallback)
{}

bool FCmdCommandReceiver::Begin()
{
    // TODO loop
}