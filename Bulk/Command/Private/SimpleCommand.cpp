#include "SimpleCommand.h"

#include <memory>

using namespace Bulk;

std::shared_ptr<ICommand> CommandFactory::Create(const std::string& inRawCommand)
{
  return std::make_shared<FSimpleCommand>(inRawCommand);
}

FSimpleCommand::FSimpleCommand(const std::string& inRawCommand)
  : ICommand(inRawCommand)
{}

bool FSimpleCommand::Execute()
{
  // it does nothing
  return true;
}