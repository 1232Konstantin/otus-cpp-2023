#pragma once

#include <functional>
#include <string>
#include <iostream>

#include "IGUI.h"

namespace Editor
{
  template <class ArgumentType>
  class FInputButton : public IDrawable
  {
  public:

    FInputButton(const std::string& InName, bool InIsVisible, const std::function<bool(const ArgumentType& Arg)>& InFunc)
      : isPressed(false)
      , Name(InName)
      , Func(InFunc)
    {
      isVisible = InIsVisible;
    }

    bool Fire(const ArgumentType& Arg)
    {
      isPressed = true;
      return Func(Arg);
    }

    // Inherited via IDrawable
    virtual void Draw() override
    {
      if (isPressed)
      {
        std::cout << "Pressed ";
        isPressed = false;
      }
      std::cout << "Button \"" << Name << "\"";
    }

  private:

    bool isPressed;
    std::string Name;
    std::function<bool(const ArgumentType& Arg)> Func;
    
  };
}
