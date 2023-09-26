/**
 * @file ICommandReceiver.h
 * @author Dabudabot
 * @breif Interface for receiving commands
 */

#pragma once

#include <functional>
#include <string>
#include <memory>

namespace Bulk
{
    using OnCommandReceived = std::function<void (const std::string&, bool)>;

    /**
     * @breif Interface for receiving commands
     */
    class ICommandReceiver
    {
    protected:

        OnCommandReceived CommandReceivedCallback;

        /**
         * @breif Ctor which accepts callback
         */
        explicit ICommandReceiver(const OnCommandReceived& inCommandReceivedCallback)
            : CommandReceivedCallback(inCommandReceivedCallback)
        {}

    public:

        virtual ~ICommandReceiver() = default;

        /**
         * @breif Loop until EOF waiting for commands and sending them to the callback
         * @return false if crashes, true if exits normally
         */
        virtual bool Begin() = 0;

        friend class CommandReceiverFactory;
    };

    /**
     * @breif Factory to build specific CommandReceiver
     */
    class CommandReceiverFactory
    {
    public:

        /**
         * @breif create CommandReceiver object
         * @return shared pointer to the CommandReceiver
         */
        static std::shared_ptr<ICommandReceiver> Create(const OnCommandReceived& inCommandReceivedCallback);
    };
}