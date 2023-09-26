/**
 * @file ICommandLogger.h
 * @author Dabudabot
 * @breif Interface for logging commands
 */

#pragma once

#include <string>
#include <memory>

namespace Bulk
{
    /**
     * @breif Interface for receiving commands
     */
    class ICommandLogger
    {
    private:

    public:

        virtual ~ICommandLogger() = default;

        /**
         * @breif Log command output
         */
        virtual void Log(const std::string& str) = 0;

        friend class CommandLoggerFactory;
    };

    /**
     * @breif Factory to build specific CommandLogger
     */
    class CommandLoggerFactory
    {
    public:

        /**
         * @breif create CommandLogger object
         * @return shared pointer to the CommandLogger
         */
        static std::shared_ptr<ICommandLogger> Create();
    };
}