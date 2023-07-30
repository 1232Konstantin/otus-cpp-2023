#include "Storage.h"

#include <memory>

using namespace Editor;

std::shared_ptr<IStorage> StorageFactory::Create(std::shared_ptr<IGUI> InGui)
{
  return std::make_shared<FStorage>(InGui);
}

FStorage::FStorage(const std::shared_ptr<IGUI>& InGui)
  : Gui(InGui)
  , CurrentDocument(nullptr)
{
}

bool FStorage::CreateDocument(const std::string& DocName)
{
  CurrentDocument = std::make_shared<FDocument>();
  Gui->Add(CurrentDocument);
  return CurrentDocument->Create(DocName);
}

bool FStorage::ImportDocument(const std::string& DocName)
{
  CurrentDocument = std::make_shared<FDocument>();
  Gui->Add(CurrentDocument);
  return CurrentDocument->Import(DocName);
}

bool FStorage::ExportDocument(const std::string& DocName)
{
  if (!CurrentDocument) return false;
  return CurrentDocument->Export(DocName);
}

bool FStorage::CreatePrimitive(const std::vector<std::pair<int, int>>& Coords)
{
  if (!CurrentDocument) return false;
  return CurrentDocument->AddPrimitives(Coords);
}

bool FStorage::DeleteLastNPrimitives(const size_t& N)
{
  if (!CurrentDocument) return false;
  return CurrentDocument->RemovePrimitives(N);
}
