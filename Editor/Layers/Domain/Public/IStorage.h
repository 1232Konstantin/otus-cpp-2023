/**
 * @file IStorage.h
 * @author Dabudabot
 * @breif Interface of the model
 */

#pragma once

#include <memory>
#include <vector>
#include <string>

#include "IGUI.h"

namespace Editor
{
  /**
   * @breif Interface of the model class
   */
  class IStorage
  {
  public:
    virtual ~IStorage() = default;

    /**
     * @breif creates document
     * @param DocName - name to be created
     * @return bool - true if success and false if fail
     */
    virtual bool CreateDocument(const std::string& DocName) = 0;

    /**
     * @breif imports document
     * @param DocName - name to be imported
     * @return bool - true if success and false if fail
     */
    virtual bool ImportDocument(const std::string& DocName) = 0;

    /**
     * @breif exports document
     * @param DocName - name to be exported
     * @return bool - true if success and false if fail
     */
    virtual bool ExportDocument(const std::string& DocName) = 0;

    /**
     * @breif creates primitive in document
     * @param Coords - primitives points
     * @return bool - true if success and false if fail
     */
    virtual bool CreatePrimitive(const std::vector<std::pair<int, int>>& Coords) = 0;

    /**
     * @breif deletes last n created primitives
     * @param N - amount of primitives to delete
     * @return bool - true if success and false if fail
     */
    virtual bool DeleteLastNPrimitives(const size_t& N) = 0;
  };

  /**
   * @breif Factory to build specific Model
   */
  class StorageFactory
  {
  public:

    /**
     * @breif create model object
     * @param InGui - Gui that will register all elements that need to be drawn
     * @return shared pointer to the model
     */
    static std::shared_ptr<IStorage> Create(std::shared_ptr<IGUI> InGui);
  };
}
