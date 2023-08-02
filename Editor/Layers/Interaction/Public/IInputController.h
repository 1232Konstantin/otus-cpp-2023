/**
 * @file IInputController.h
 * @author Dabudabot
 * @breif Interface of the controller
 */

#pragma once

#include <memory>
#include <vector>
#include <string>

#include "IGUI.h"
#include "IStorage.h"

namespace Editor
{
  /**
   * @breif Interface of the contoller class
   */
  class IInputController
  {
  public:
    virtual ~IInputController() = default;

    /**
     * @breif send command to the button to create document
     * @param DocName - name to be created
     * @return bool - true if success and false if fail
     */
    virtual bool CreateDocument(const std::string& DocName) = 0;

    /**
     * @breif send command to the button to import document
     * @param DocName - name to be imported
     * @return bool - true if success and false if fail
     */
    virtual bool ImportDocument(const std::string& DocName) = 0;

    /**
     * @breif send command to the button to export document
     * @param DocName - name to be exported
     * @return bool - true if success and false if fail
     */
    virtual bool ExportDocument(const std::string& DocName) = 0;

    /**
     * @breif send command to the button to create primitive in document
     * @param Coords - primitives points
     * @return bool - true if success and false if fail
     */
    virtual bool CreatePrimitive(const std::vector<std::pair<int, int>>& Coords) = 0;

    /**
     * @breif send command to the button to delete last n created primitives
     * @param N - amount of primitives to delete
     * @return bool - true if success and false if fail
     */
    virtual bool DeleteLastNPrimitives(const size_t& N) = 0;
  };

  /**
   * @breif Factory to build specific Contoller
   */
  class InputControllerFactory
  {
  public:

    /**
     * @breif create contoller object
     * @param InGui - Gui that will register all controls that need to be drawn
     * @param InStorage - Model that is contolled by the controller
     * @return shared pointer to the controller
     */
    static std::shared_ptr<IInputController> Create(const std::shared_ptr<IGUI>& InGui, const std::shared_ptr<IStorage>& InStorage);
  };
}
