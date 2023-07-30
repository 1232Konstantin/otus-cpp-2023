#include "GUI.h"

#include <memory>
#include <iostream>

using namespace Editor;

std::shared_ptr<IGUI> GUIFactory::Create()
{
  return std::make_shared<FGUI>();
}

void FGUI::DrawAll()
{
  std::cout << "you see: \n";

  Drawables.erase(
    std::remove_if(
      Drawables.begin(),
      Drawables.end(),
      [](std::weak_ptr<IDrawable> x) { return x.expired(); }
    ),
    Drawables.end()
  );

  for (const auto& drawable : Drawables)
  {
    if (std::shared_ptr<IDrawable> spt = drawable.lock())
    {
      if (spt->isVisible)
      {
        std::cout << '\t';
        spt->Draw();
        std::cout << '\n';
      }
    }
  }
}

void FGUI::Add(std::weak_ptr<IDrawable> Drawable)
{
  Drawables.push_back(Drawable);
}
