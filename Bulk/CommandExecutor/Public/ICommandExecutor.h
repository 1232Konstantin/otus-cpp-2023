/**
 * @file ICommandExecutor.h
 * @author Dabudabot
 * @breif Interface for executing commands
 */

#pragma once

#include "ICommand.h"
#include "ICommandLogger.h"

#include <memory>
#include <queue>

namespace Bulk
{
    class CommandExecutorState_Base
    {
    private:

        ICommandExecutor& CommandExecutor;

    public:

        /**
         * @breif Ctor with reference to the executor, to control it
         */
        explicit CommandExecutorState_Base(ICommandExecutor& inCommandExecutor) 
            : CommandExecutor(inCommandExecutor)
        {}

        /**
         * @breif Adding command according to the state
         */
        virtual bool AddCommandImpl(std::shared_ptr<ICommand> Command) = 0;

        /**
         * @breif Logic on EOF according to the state
         */
        virtual bool OnEOFImpl() = 0;
    };

    class CommandExecutorState_Normal : public CommandExecutorState_Base
    {
    public:

        /**
         * @breif Ctor with reference to the executor, to control it
         */
        explicit CommandExecutorState_Normal(ICommandExecutor& inCommandExecutor) 
            : CommandExecutorState_Base(inCommandExecutor)
        {}

        /**
         * @breif Adding command according to the state
         */
        virtual bool AddCommandImpl(std::shared_ptr<ICommand> Command) override;

        /**
         * @breif Logic on EOF according to the state
         */
        virtual bool OnEOFImpl() override;
    };

    class CommandExecutorState_Dynamic : public CommandExecutorState_Base
    {
    public:

        /**
         * @breif Ctor with reference to the executor, to control it
         */
        explicit CommandExecutorState_Dynamic(ICommandExecutor& inCommandExecutor) 
            : CommandExecutorState_Base(inCommandExecutor)
        {}

        /**
         * @breif Adding command according to the state
         */
        virtual bool AddCommandImpl(std::shared_ptr<ICommand> Command) override;

        /**
         * @breif Logic on EOF according to the state
         */
        virtual bool OnEOFImpl() override;
    };

    /**
     * @breif Interface for receiving commands
     */
    class ICommandExecutor
    {
    protected:

        const size_t BulkSize = 1;
        bool isDynamicBlock = false;
        std::queue<std::shared_ptr<ICommand>> CommandQueue;

        std::shared_ptr<ICommandLogger> Logger = nullptr;

        std::unique_ptr<CommandExecutorState_Base> State = nullptr;

        /**
         * @breif Ctor which accepts default size of the bulk and logger to log command completion
         */
        explicit ICommandExecutor(const size_t& inBulkSize, std::unique_ptr<CommandExecutorState_Base> inState, std::shared_ptr<ICommandLogger> inLogger)
            : BulkSize(inBulkSize)
            , isDynamicBlock(false)
            , Logger(inLogger)
            , State(std::move(inState))
        {}

    public:

        virtual ~ICommandExecutor() = default;

        /**
         * @breif Add command to the queue, as queue will reach bulk size or dynamic block ends, commands will be executed
         */
        virtual bool AddCommand(std::shared_ptr<ICommand> Command) = 0;

        /**
         * @breif Logic to be triggered on EOF
         */
        virtual bool OnEOF() = 0;

        /**
         * @breif Chaning state of the executor
         */
        virtual void SetState(std::unique_ptr<CommandExecutorState_Base> inState) = 0;

        friend class CommandExecutorState_Base;
    };

    /**
     * @breif Factory to build specific CommandExecutor
     */
    class CommandExecutorFactory
    {
    public:

        /**
         * @breif create CommandExecutor object
         * @return shared pointer to the CommandExecutor
         */
        static std::shared_ptr<ICommandExecutor> Create(const size_t& inBulkSize, std::shared_ptr<ICommandLogger> inLogger);
    };
}