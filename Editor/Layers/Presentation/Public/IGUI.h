/**
 * @file IGUI.h
 * @author Dabudabot
 * @breif Interface of the GUI
 */

#pragma once

#include <vector>
#include <memory>

namespace Editor
{
  /**
   * @breif Inherit from this if you need your class to be drawn
   */
  class IDrawable
  {
  public:
    virtual ~IDrawable() = default;

    /**
     * @breif Logic how to draw this element
     */
    virtual void Draw() = 0;

    /**
     * @breif switch to enable or disable drawing
     */
    bool isVisible = true;
  };

  /**
   * @breif Interface of the GUI class
   */
  class IGUI
  {
  public:
    virtual ~IGUI() = default;

    /**
     * @breif draw all added IDrawables
     */
    virtual void DrawAll() = 0;

    /**
     * @breif add IDrawable to be drawn
     * @param Drawable - weak pointer to the object to be drawn
     */
    virtual void Add(std::weak_ptr<IDrawable> Drawable) = 0;
  };

  /**
   * @breif Factory to build specific GUI
   */
  class GUIFactory
  {
  public:

    /**
     * @breif create GUI object
     * @return shared pointer to the GUI
     */
    static std::shared_ptr<IGUI> Create();
  };
}
