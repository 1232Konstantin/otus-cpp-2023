/**
 * @file CmdApplication.h
 * @author Dabudabot
 * @breif Core of the cmd verion of the editor
 */

#pragma once

#include <iostream>
#include <memory>
#include <sstream>

#include "IStorage.h"
#include "IInputController.h"
#include "IGUI.h"

namespace Editor
{
  /**
   * @breif Class containing main application loop
   */
  class FCmdApplication
  {
  public:

    /**
     * @breif Ctor which could accept different stream containing commands for the application
     */
    explicit FCmdApplication(std::istream& in = std::cin);

    /**
     * @breif Application start
     * @return false if app crashes, true if exits normally
     */
    bool Begin();

    /**
     * @breif Application main loop
     * @return false if app crashes, true if exits normally
     */
    bool EventLoop();

  private:

    /**
     * @breif Processing stream input here
     * @return false if input cannot be processed
     */
    bool HandleInput();

    /**
     * Stream holder
     */
    std::istream& Stream;

    /**
     * Main state of the application
     */
    bool IsRunning = true;

    /**
     * Holds view of the app
     */
    std::shared_ptr<IGUI> Gui;

    /**
     * Holds model of the app
     */
    std::shared_ptr<IStorage> Storage;

    /**
     * Holds controller of the app
     */
    std::shared_ptr<IInputController> InputController;
  };
}
