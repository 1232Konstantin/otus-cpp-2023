/**
 * @file ICommand.h
 * @author Dabudabot
 * @breif Commands interface
 */

#pragma once

#include <string>
#include <chrono>
#include <memory>

namespace Bulk
{
  /**
   * @breif Interface for receiving commands
   */
  class ICommand
  {
  private:

    const std::string RawCommand;
    const std::chrono::time_point<std::chrono::system_clock> CommandTime;

  protected:

    /**
     * @breif Ctor which accepts default size of the bulk and logger to log command completion
     */
    explicit ICommand(const std::string& inRawCommand)
      : RawCommand(inRawCommand)
      , CommandTime(std::chrono::system_clock::now())
    {}

  public:

    virtual ~ICommand() = default;

    /**
     * @breif Execute payload of the command
     */
    virtual bool Execute() = 0;

    /**
     * @breif Return raw command
     */
    virtual std::string GetRawCommand() { return RawCommand; }
  };

  /**
   * @breif Factory to build specific Command
   */
  class CommandFactory
  {
  public:

    /**
     * @breif create Command object
     * @return shared pointer to the Command
     */
    static std::shared_ptr<ICommand> Create(const std::string& inRawCommand);
  };
}