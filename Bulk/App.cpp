#include "App.h"

#include <memory>
#include <string>

using namespace Bulk;

FBulkApp::FBulkApp(const size_t& inBulkSize)
  : BulkSize(inBulkSize)
{
  Logger = CommandLoggerFactory::Create();

  Executor = CommandExecutorFactory::Create(inBulkSize, Logger);

  Receiver = CommandReceiverFactory::Create(
    [this](const std::string& ReceivedRawCommand, bool isEOF)
    {
      if (isEOF)
      {
        this->Executor->OnEOF();
        return;
      }

      if ("{" == ReceivedRawCommand)
      {
        this->Executor->SetState(std::make_unique<CommandExecutorState_Dynamic>(*(this->Executor)));
        return;
      }

      if ("}" == ReceivedRawCommand)
      {
        this->Executor->SetState(std::make_unique<CommandExecutorState_Normal>(*(this->Executor)));
        return;
      }

      this->Executor->AddCommand(CommandFactory::Create(ReceivedRawCommand));
    }
  );
}

bool FBulkApp::Begin()
{
  return Receiver->Begin();
}
