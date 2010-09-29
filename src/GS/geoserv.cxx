/*                       G M A I N . C X X
 * BRL-CAD
 *
 * Copyright (c) 2010 United States Government as represented by
 * the U.S. Army Research Laboratory.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * version 2.1 as published by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this file; see the file named COPYING for more
 * information.
 */
/** @file geoserv.cxx
 *
 * Brief description
 *
 */

#include "GeometryService.h"

#include "libalf.h"
#include "libutility.h"
#include "libevent.h"

#include <iostream>
#include <stdlib.h>

#include <QtCore/QString>

int main(int argc, char* argv[])
{
    std::cout << std::endl << std::endl;
    Logger* log = Logger::getInstance();
    log->logBANNER("geoserv", "GeometryService Config Loader");

    Config* c = Config::getInstance();

    //TODO Configure system loads stuff here
    if (c->loadFile("geoserve.config", true)) {
	return 1;
    }

    QString localNodename = c->getConfigValue("LocalNodeName");
    if (localNodename == "") {
    	localNodename = "DefaultGSNodename";
    }


    log->logBANNER("geoserv", "Booting GeometryService: " + localNodename);

    QString sport = c->getConfigValue("ListenPort");
    if (sport == NULL){
    	log->logERROR("geoserv", "Config File does not contain a 'ListenPort' parameter");
    	return 1;
    }
    if (sport.length() <= 0){
    	log->logERROR("geoserv", "Config File contains a 'ListenPort' key, however the value was <= 0.");
    	return 1;
    }

    bool ok;
    quint16 port = sport.toUShort(&ok, 10);
    if (!ok){
    	log->logERROR("geoserv", "Config File contains a 'ListenPort' key, however the value failed to parse to a valid number.");
    	return 1;
    }

    bool daemon = false;

    GeometryService* gs = new GeometryService(localNodename, port);

    if (daemon){
    	gs->start();
    }


    return 0;
}
