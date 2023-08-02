#pragma once

#include "IGUI.h"

#include <vector>

namespace Editor
{
  class FGUI : public IGUI
  {
  public:
    // Inherited via IGUI
    virtual void DrawAll() override;
    virtual void Add(std::weak_ptr<IDrawable> Drawable) override;

  private:
    std::vector<std::weak_ptr<IDrawable>> Drawables;
  };
}
