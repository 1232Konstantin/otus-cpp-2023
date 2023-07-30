#pragma once

#include <memory>
#include <vector>
#include <string>

#include "IGUI.h"

namespace Editor
{
  class IStorage
  {
  public:
    virtual ~IStorage() = default;
    virtual bool CreateDocument(const std::string& DocName) = 0;
    virtual bool ImportDocument(const std::string& DocName) = 0;
    virtual bool ExportDocument(const std::string& DocName) = 0;
    virtual bool CreatePrimitive(const std::vector<std::pair<int, int>>& Coords) = 0;
    virtual bool DeleteLastNPrimitives(const size_t& N) = 0;
  };

  class StorageFactory
  {
  public:
    static std::shared_ptr<IStorage> Create(std::shared_ptr<IGUI> InGui);
  };
}
