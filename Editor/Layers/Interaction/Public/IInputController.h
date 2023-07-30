#pragma once

#include <memory>
#include <vector>
#include <string>

#include "IGUI.h"
#include "IStorage.h"

namespace Editor
{
  class IInputController
  {
  public:
    virtual ~IInputController() = default;
    virtual bool CreateDocument(const std::string& DocName) = 0;
    virtual bool ImportDocument(const std::string& DocName) = 0;
    virtual bool ExportDocument(const std::string& DocName) = 0;
    virtual bool CreatePrimitive(const std::vector<std::pair<int, int>>& Coords) = 0;
    virtual bool DeleteLastNPrimitives(const size_t& N) = 0;
  };

  class InputControllerFactory
  {
  public:
    static std::shared_ptr<IInputController> Create(const std::shared_ptr<IGUI>& InGui, const std::shared_ptr<IStorage>& InStorage);
  };
}
