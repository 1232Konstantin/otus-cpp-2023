#pragma once

#include <memory>

#include "IInputController.h"
#include "InputButton.h"

namespace Editor
{
  class FInputController : public IInputController
  {
  public:

    FInputController(const std::shared_ptr<IGUI>& InGui, const std::shared_ptr<IStorage>& InStorage);

    // Inherited via IInputController
    virtual bool CreateDocument(const std::string& DocName) override;
    virtual bool ImportDocument(const std::string& DocName) override;
    virtual bool ExportDocument(const std::string& DocName) override;
    virtual bool CreatePrimitive(const std::vector<std::pair<int, int>>& Coords) override;
    virtual bool DeleteLastNPrimitives(const size_t& N) override;

  private:

    std::shared_ptr<IGUI> Gui;
    std::shared_ptr<IStorage> Storage;

    std::shared_ptr<FInputButton<std::string>> CreateDocumentBtn;
    std::shared_ptr<FInputButton<std::string>> ImportDocumentBtn;
    std::shared_ptr<FInputButton<std::string>> ExportDocumentBtn;
    std::shared_ptr<FInputButton<std::vector<std::pair<int, int>>>> CreatePrimitiveBtn;
    std::shared_ptr<FInputButton<size_t>> DeleteLastNPrimitivesBtn;
  };
}

