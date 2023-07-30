#pragma once

#include <iostream>
#include <vector>

namespace Editor
{
  class FPrimitive
  {
  public:

    explicit FPrimitive(const std::vector<std::pair<int, int>>& InCoords);

  private:

    std::vector<std::pair<int, int>> Coords;

    friend std::ostream& operator<<(std::ostream&, const FPrimitive&);
  };

  std::ostream& operator<< (std::ostream& os, const FPrimitive& t);
}