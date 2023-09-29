#pragma once

#include "ICommandExecutor.h"

#include <string>

namespace Bulk
{
  class FSimpleCommandExecutor : public ICommandExecutor
  {
  public:
    explicit FSimpleCommandExecutor(const size_t& inBulkSize, std::shared_ptr<ICommandLogger> inLogger);

    virtual bool AddCommand(std::shared_ptr<ICommand> Command) override;
    virtual bool AddCommand_Normal(std::shared_ptr<ICommand> Command) override;
    virtual bool AddCommand_Dynamic(std::shared_ptr<ICommand> Command) override;
    virtual bool OnEOF() override;
    virtual bool OnEOF_Normal() override;
    virtual bool OnEOF_Dynamic() override;
    virtual void SetState(std::unique_ptr<CommandExecutorState_Base> inState) override;
  };
}