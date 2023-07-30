#include "Primitive.h"

using namespace Editor;

FPrimitive::FPrimitive(const std::vector<std::pair<int, int>>& InCoords)
  : Coords(InCoords)
{
}

std::ostream& Editor::operator<<(std::ostream& os, const FPrimitive& t)
{
  for (const auto& [x, y] : t.Coords)
  {
    os << '(' << x << ',' << y << ") ";
  }
  return os;
}
