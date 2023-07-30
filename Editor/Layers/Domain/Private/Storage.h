#pragma once

#include "IStorage.h"
#include "Document.h"

#include <memory>

namespace Editor
{
  class FStorage : public IStorage
  {
  public:
    FStorage(const std::shared_ptr<IGUI>& InGui);

    // Inherited via IStorage
    virtual bool CreateDocument(const std::string& DocName) override;
    virtual bool ImportDocument(const std::string& DocName) override;
    virtual bool ExportDocument(const std::string& DocName) override;
    virtual bool CreatePrimitive(const std::vector<std::pair<int, int>>& Coords) override;
    virtual bool DeleteLastNPrimitives(const size_t& N) override;

  private:

    std::shared_ptr<IGUI> Gui;
    std::shared_ptr<FDocument> CurrentDocument;

  };

}