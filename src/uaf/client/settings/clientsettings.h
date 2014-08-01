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

#ifndef UAFC_CLIENTSETTINGS_H_
#define UAFC_CLIENTSETTINGS_H_

// STD
#include <string>
#include <sstream>
#include <vector>
// SDK
// UAF
#include "uaf/util/util.h"
#include "uaf/util/loglevels.h"
#include "uaf/util/stringifiable.h"
#include "uaf/client/clientexport.h"


namespace uafc
{


    /*******************************************************************************************//**
    * An uafc::ClientSettings instance holds the settings of a uafc::Client instance.
    *
    * @ingroup ClientSettings
    ***********************************************************************************************/
    class UAFC_EXPORT ClientSettings
    {
    public:


        /**
         * Create a default ClientSettings instance.
         *
         * Default values are:
         *  - applicationName : ""
         *  - applicationUri : ""
         *  - productUri : ""
         *  - localeId : ""
         *  - discoveryFindServersTimeoutSec : 2.0
         *  - discoveryGetEndpointsTimeoutSec : 1.0
         *  - discoveryIntervalSec : 30.0
         *  - logToStdOutLevel : uaf::loglevels::Disabled
         *  - logToCallbackLevel : uaf::loglevels::Disabled
         *  - certificateTrustListLocation : "PKI/trusted/certs/"
         *  - certificateRevocationListLocation : "PKI/trusted/crl/"
         *  - issuersCertificatesLocation : "PKI/issuers/certs/"
         *  - issuersRevocationListLocation : "PKI/issuers/crl/"
         *  - clientPrivateKey : "PKI/client/private/client.pem"
         *  - clientCertificate : "PKI/client/certs/client.der"
         */
        ClientSettings();


        /**
         * Create a ClientSettings instance with default values except the name.
         */
        ClientSettings(const std::string& applicationName);


        /**
         * Create a ClientSettings instance with default values except the name and discoveryUrls.
         */
        ClientSettings(const std::string&               applicationName,
                       const std::vector<std::string>&  discoveryUrls);


        /////// Main ///////


        /** The application name of the client. */
        std::string applicationName;

        /** The unique application URI of the client. */
        std::string applicationUri;

        /** The unique product URI. */
        std::string productUri;

        /** The Locale identifier (e.g. "en", "de", "en-US", ...). */
        std::string localeId;


        /////// Logging ///////


        /** When logging to the stdout, only log messages from at least this loglevel. */
        uaf::loglevels::LogLevel logToStdOutLevel;

        /** When logging to the callback interface, only log messages from at least this loglevel.*/
        uaf::loglevels::LogLevel logToCallbackLevel;


        /////// Discovery ///////


        /** A list of the Servers and DiscoveryServers the client should be able to discover. */
        std::vector<std::string> discoveryUrls;

        /** The timeout value for the FindServers discovery service, in seconds. */
        float discoveryFindServersTimeoutSec;

        /** The timeout value for the GetEndpoints discovery service, in seconds. */
        float discoveryGetEndpointsTimeoutSec;

        /** The interval between discovery attempts which are continuously running in the
         *  background, in seconds. */
        float discoveryIntervalSec;


        /////// Security ///////

        /** The trust list location.
         *
         *  This directory can be specified either as an absolute path, or as a path relative to
         *  the application path.
         *
         *  Default: "PKI/trusted/certs/". */
        std::string certificateTrustListLocation;

        /** The revocation list location.
         *
         *  This directory can be specified either as an absolute path, or as a path relative to
         *  the application path.
         *
         *  Default: "PKI/trusted/crl/" */
        std::string certificateRevocationListLocation;

        /** The issuers certificates location.
         *
         *  This directory can be specified either as an absolute path, or as a path relative to
         *  the application path.
         *
         *  Default: "PKI/issuers/certs/". */
        std::string issuersCertificatesLocation;

        /** The issuers revocation list location.
         *
         *  This directory can be specified either as an absolute path, or as a path relative to
         *  the application path.
         *
         *  Default: "PKI/issuers/crl/". */
        std::string issuersRevocationListLocation;


        /** The private key of this client application.
         *
         *  This file can be specified either as an absolute path, or as a path relative to
         *  the application path.
         *
         *  Default: "PKI/client/private/client.pem". */
        std::string clientPrivateKey;


        /** The certificate of this client application.
         *
         *  This file can be specified either as an absolute path, or as a path relative to
         *  the application path.
         *
         *  Default: "PKI/client/certs/client.der". */
        std::string clientCertificate;


        /**
         * Get a nice string representation of the settings.
         *
         * @param indent Indentation to add to each line (e.g. "  " to indent with 2 spaces).
         * @param colon  The position to put the colon (double point).
         * @return       A string representation (multiple lines, separated by newline-characters).
         */
        std::string toString(const std::string& indent="", std::size_t colon=50) const;


        // comparison operators
        friend UAFC_EXPORT bool operator< (
                const ClientSettings& object1,
                const ClientSettings& object2);
        friend UAFC_EXPORT bool operator==(
                const ClientSettings& object1,
                const ClientSettings& object2);
        friend UAFC_EXPORT bool operator!=(
                const ClientSettings& object1,
                const ClientSettings& object2);

    };


}





#endif /* UAFC_CLIENTSETTINGS_H_ */
