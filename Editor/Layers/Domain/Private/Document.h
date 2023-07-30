#pragma once

#include <string>
#include <vector>

#include "IGUI.h"
#include "Primitive.h"

namespace Editor
{
  class FDocument : public IDrawable
  {
  public:

    bool Create(const std::string& InDocName);
    bool Import(const std::string& InDocName);
    bool Export(const std::string& InDocName);
    bool AddPrimitives(const std::vector<std::pair<int, int>>& InCoordinates);
    bool RemovePrimitives(const size_t& N);

    // Inherited via IDrawable
    virtual void Draw() override;

  private:

    std::string DocName = "";
    std::string ExportName = "";
    bool isImported = false;
    bool isCreated = false;
    bool isExported = false;
    std::vector<FPrimitive> Primitives;

  };
}