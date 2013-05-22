/* This file is part of the UAF (Unified Architecture Framework) project.
 *
 * Copyright (C) 2012 Wim Pessemier (Institute of Astronomy, KULeuven)
 *
 * Project website: http://www.ster.kuleuven.be/uaf
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "uaf/client/invocations/writeinvocation.h"

namespace uafc
{
    using namespace uaf;
    using namespace uafc;
    using std::string;
    using std::stringstream;
    using std::vector;


    // Fill the synchronous SDK members
    // =============================================================================================
    Status WriteInvocation::fromSyncUafToSdk(
            const vector<WriteRequestTarget>&   targets,
            const WriteSettings&                settings,
            const NamespaceArray&               nameSpaceArray,
            const ServerArray&                  serverArray)
    {
        Status ret;

        // update the uaServiceSettings_
        ret = settings.toSdk(uaServiceSettings_);

        // declare the number of targets
        size_t noOfTargets = targets.size();

        // resize the number of uaReadValueIds_
        uaWriteValues_.create(noOfTargets);

        // loop through the targets
        for (size_t i = 0; i < noOfTargets && ret.isGood(); i++)
        {
            // update the node id of the target
            ret = nameSpaceArray.fillOpcUaNodeId(targets[i].address, uaWriteValues_[i].NodeId);

            // only update the rest of the SDK variables if no error has occurred yet
            if (ret.isGood())
            {
                // update the attribute id, index range, data and status code of the target
                uaWriteValues_[i].AttributeId = targets[i].attributeId;
                UaString(targets[i].indexRange.c_str()).copyTo(&uaWriteValues_[i].IndexRange);

                // copy the data value
                targets[i].toSdk(&uaWriteValues_[i].Value);
            }
        }

        return ret;
    }



    // Fill the asynchronous SDK members
    // =============================================================================================
    Status WriteInvocation::fromAsyncUafToSdk(
            const vector<WriteRequestTarget>&   targets,
            const WriteSettings&                settings,
            const NamespaceArray&               nameSpaceArray,
            const ServerArray&                  serverArray)
    {
        // same as synchronous
        return fromSyncUafToSdk(targets, settings, nameSpaceArray, serverArray);
    }


    // Invoke the service synchronously
    // =============================================================================================
    Status WriteInvocation::invokeSyncSdkService(UaClientSdk::UaSession* uaSession)
    {
        Status ret;

        UaStatus uaStatus = uaSession->write(
                uaServiceSettings_,
                uaWriteValues_,
                uaStatusCodes_,
                uaDiagnosticInfos_);

        ret.fromSdk(uaStatus.statusCode(), "Synchronous write invocation failed");

        return ret;
    }


    // Invoke the service asynchronously
    // =============================================================================================
    Status WriteInvocation::invokeAsyncSdkService(
            UaClientSdk::UaSession* uaSession,
            TransactionId           transactionId)
    {
        Status ret;

        UaStatus uaStatus = uaSession->beginWrite(
                uaServiceSettings_,
                uaWriteValues_,
                transactionId);

        ret.fromSdk(uaStatus.statusCode(), "Asynchronous write invocation failed");

        return ret;
    }




    // Fill the UAF members
    // =============================================================================================
    Status WriteInvocation::fromSyncSdkToUaf(
            const NamespaceArray&       nameSpaceArray,
            const ServerArray&          serverArray,
            vector<WriteResultTarget>&  targets)
    {
        // declare the return Status
        Status ret;

        // declare the number of targets, and resize the output parameter accordingly
        uint32_t noOfTargets = uaStatusCodes_.length();
        targets.resize(noOfTargets);

        // check the number of targets
        if (noOfTargets == uaWriteValues_.length())
        {

            for (uint32_t i=0; i<noOfTargets ; i++)
            {
                // update the value and the status
                targets[i].status.fromSdk(uaStatusCodes_[i],
                                          "The server reported a write failure");
            }

            ret.setGood();
        }
        else
        {
            ret.setStatus(statuscodes::UnexpectedError,
                          "Number of targets does not match number of targets");
        }

        return ret;
    }




}
