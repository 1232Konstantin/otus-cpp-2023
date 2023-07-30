#include "InputController.h"

#include <memory>

using namespace Editor;

std::shared_ptr<IInputController> InputControllerFactory::Create(const std::shared_ptr<IGUI>& InGui, const std::shared_ptr<IStorage>& InStorage)
{
  return std::make_shared<FInputController>(InGui, InStorage);
}

FInputController::FInputController(const std::shared_ptr<IGUI>& InGui, const std::shared_ptr<IStorage>& InStorage)
  : Gui(InGui), Storage(InStorage)
{
  CreateDocumentBtn = std::make_shared<FInputButton<std::string>>(
    "CreateDocument", 
    true, 
    std::bind(&IStorage::CreateDocument, &(*Storage), std::placeholders::_1)
  );
  
  ImportDocumentBtn = std::make_shared<FInputButton<std::string>>(
    "ImportDocument", 
    true, 
    std::bind(&IStorage::ImportDocument, &(*Storage), std::placeholders::_1)
  );

  ExportDocumentBtn = std::make_shared<FInputButton<std::string>>(
    "ExportDocument", 
    false, 
    std::bind(&IStorage::ExportDocument, &(*Storage), std::placeholders::_1)
  );
  
  CreatePrimitiveBtn = std::make_shared<FInputButton<std::vector<std::pair<int, int>>>>(
    "CreatePrimitive", 
    false, 
    std::bind(&IStorage::CreatePrimitive, &(*Storage), std::placeholders::_1)
  );

  DeleteLastNPrimitivesBtn = std::make_shared<FInputButton<size_t>>(
    "DeleteLastNPrimitives", 
    false, 
    std::bind(&IStorage::DeleteLastNPrimitives, &(*Storage), std::placeholders::_1)
  );
  
  Gui->Add(CreateDocumentBtn);
  Gui->Add(ImportDocumentBtn);
  Gui->Add(ExportDocumentBtn);
  Gui->Add(CreatePrimitiveBtn);
  Gui->Add(DeleteLastNPrimitivesBtn);
}

bool FInputController::CreateDocument(const std::string& DocName)
{
  ExportDocumentBtn->isVisible = true;
  CreatePrimitiveBtn->isVisible = true;
  DeleteLastNPrimitivesBtn->isVisible = true;
  return CreateDocumentBtn->Fire(DocName);
}

bool FInputController::ImportDocument(const std::string& DocName)
{
  ExportDocumentBtn->isVisible = true;
  CreatePrimitiveBtn->isVisible = true;
  DeleteLastNPrimitivesBtn->isVisible = true;
  return ImportDocumentBtn->Fire(DocName);
}

bool FInputController::ExportDocument(const std::string& DocName)
{
  return ExportDocumentBtn->Fire(DocName);
}

bool FInputController::CreatePrimitive(const std::vector<std::pair<int, int>>& Coords)
{
  return CreatePrimitiveBtn->Fire(Coords);
}

bool FInputController::DeleteLastNPrimitives(const size_t& N)
{
  return DeleteLastNPrimitivesBtn->Fire(N);
}