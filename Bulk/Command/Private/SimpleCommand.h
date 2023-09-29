#pragma once

#include "ICommand.h"

#include <string>

namespace Bulk
{
  class FSimpleCommand : public ICommand
  {
  public:
    explicit FSimpleCommand(const std::string& inRawCommand);

    virtual bool Execute() override;
  };
}