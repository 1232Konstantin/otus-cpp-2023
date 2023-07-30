#include "Document.h"

#include "Primitive.h"

#include <iostream>

using namespace Editor;

bool FDocument::Create(const std::string& InDocName)
{
  isCreated = true;
  DocName = InDocName;
  return true;
}

bool FDocument::Import(const std::string& InDocName)
{
  isImported = true;
  DocName = InDocName;
  return true;
}

bool FDocument::Export(const std::string& InDocName)
{
  isExported = true;
  ExportName = InDocName;
  return true;
}

bool FDocument::AddPrimitives(const std::vector<std::pair<int, int>>& InCoordinates)
{
  Primitives.emplace_back(FPrimitive{ InCoordinates });
  return true;
}

bool FDocument::RemovePrimitives(const size_t& N)
{
  size_t i = 0;
  while (i < N && !Primitives.empty())
  {
    ++i;
    Primitives.pop_back();
  }
  return true;
}

void FDocument::Draw()
{
  if (isCreated)
  {
    isCreated = false;
    std::cout << "Created ";
  }

  if (isImported)
  {
    isImported = false;
    std::cout << "Imported ";
  }

  if (isExported)
  {
    isExported = false;
    std::cout << "Exported with name " << ExportName << ' ';
  }

  std::cout << " Document with name "
    << DocName
    << " which has "
    << Primitives.size()
    << " primitives";

  for (const auto& primitive : Primitives)
  {
    std::cout << "\n\t" << primitive;
  }
}