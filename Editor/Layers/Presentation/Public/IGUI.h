#pragma once

#include <vector>
#include <memory>

namespace Editor
{
  class IDrawable
  {
  public:
    virtual ~IDrawable() = default;
    virtual void Draw() = 0;
    bool isVisible = true;
  };

  class IGUI
  {
  public:
    virtual ~IGUI() = default;
    virtual void DrawAll() = 0;
    virtual void Add(std::weak_ptr<IDrawable> Drawable) = 0;
  };

  class GUIFactory
  {
  public:
    static std::shared_ptr<IGUI> Create();
  };
}
