#include "SimpleCommandExecutor.h"

#include <memory>

using namespace Bulk;

std::shared_ptr<ICommandExecutor> CommandExecutorFactory::Create(const size_t& inBulkSize, std::shared_ptr<ICommandLogger> inLogger)
{
  return std::make_shared<FSimpleCommandExecutor>(inBulkSize, inLogger);
}

FSimpleCommandExecutor::FSimpleCommandExecutor(const size_t& inBulkSize, std::shared_ptr<ICommandLogger> inLogger)
  : ICommandExecutor(inBulkSize, inLogger)
{
  State = std::make_unique<CommandExecutorState_Normal>(*(this));
}

bool FSimpleCommandExecutor::AddCommand(std::shared_ptr<ICommand> Command)
{
  return State->AddCommandImpl(Command);
}

bool FSimpleCommandExecutor::AddCommand_Normal(std::shared_ptr<ICommand> Command)
{
  CommandQueue.push(Command);

  if (CommandQueue.size() == BulkSize)
  {
    std::string ResultLog = "";

    while (!CommandQueue.empty())
    {
      if (ResultLog.empty())
      {
        ResultLog = "bulk: ";
      }
      else
      {
        ResultLog += ", ";
      }

      auto CurrentCommand = CommandQueue.front();
      CommandQueue.pop();
      CurrentCommand->Execute();
      ResultLog += CurrentCommand->GetRawCommand();
    }

    Logger->Log(ResultLog);
  }

  return true;
}

bool FSimpleCommandExecutor::AddCommand_Dynamic(std::shared_ptr<ICommand> Command)
{
  return;
}

bool FSimpleCommandExecutor::OnEOF()
{
  return State->OnEOFImpl();
}

bool FSimpleCommandExecutor::OnEOF_Normal()
{
  return;
}

bool FSimpleCommandExecutor::OnEOF_Dynamic()
{
  return;
}

void FSimpleCommandExecutor::SetState(std::unique_ptr<CommandExecutorState_Base> inState)
{
  State = std::move(inState);
}

bool CommandExecutorState_Normal::AddCommandImpl(std::shared_ptr<ICommand> Command)
{
  return CommandExecutor.AddCommand_Normal(Command);
}

bool CommandExecutorState_Normal::OnEOFImpl()
{
  return CommandExecutor.OnEOF_Normal();
}

bool CommandExecutorState_Dynamic::AddCommandImpl(std::shared_ptr<ICommand> Command)
{
  return CommandExecutor.AddCommand_Dynamic(Command);
}

bool CommandExecutorState_Dynamic::OnEOFImpl()
{
  return CommandExecutor.OnEOF_Dynamic();
}