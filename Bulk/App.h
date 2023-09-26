/**
 * @file App.h
 * @author Dabudabot
 * @breif Core of the bulk command executor
 */

#pragma once

#include "ICommandReceiver.h"
#include "ICommandLogger.h"
#include "ICommandExecutor.h"

#include <memory>

namespace Bulk
{
    /**
     * @breif Class opearting all other classes
     */
    class FBulkApp
    {
    private:

        const size_t BulkSize = 1;

    public:

        // interface to work with receiver
        std::shared_ptr<ICommandReceiver> Receiver = nullptr;
        // interface to work with Logger (just passed to the executor)
        std::shared_ptr<ICommandLogger> Logger = nullptr;
        // interface to work with Executor
        std::shared_ptr<ICommandExecutor> Executor = nullptr;

    
        /**
         * @breif Ctor which accepts size of the default bulk
         */
        explicit FBulkApp(const size_t& inBulkSize);

        /**
         * @breif Application start, it will loop in receiver until EOF
         * @return false if app crashes, true if exits normally
         */
        bool Begin();
    };
}