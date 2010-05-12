/*                     G A T E W A Y . C X X
 * BRLCAD
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
/** @file Gateway.cxx
 *
 * Brief description
 *
 */

#include "Gateway.h"

Gateway::Gateway(QString gsHostname, INetMsgHandler* handler)
{
    this->log = Logger::getInstance();
    this->portMan = new NetPortalManager(gsHostname, handler);
}

Gateway::~Gateway()
{
    delete this->portMan;
}

void Gateway::run()
{
    this->exec();
}

void Gateway::stop()
{
    this->quit();
}

void Gateway::listen(QHostAddress address, ushort port)
{
    if (this->isRunning() == false) {
	this->log->logINFO("Gateway", "Attempted to Listen on a Gateway that is not running.");
	return;
    }
    this->portMan->listen(address, port);
}

void Gateway::stopListening(QHostAddress address, ushort port)
{
    if (this->isRunning() == false) {
        this->log->logINFO("Gateway", "Attempted to stop listening on a Gateway that is not running.");
        return;
    }

}

QList<QString> Gateway::getConnectedHostList()
{
}

void Gateway::sendToHost(QString host, NetMsg* msg)
{
    if (this->isRunning() == false) {
        this->log->logINFO("Gateway", "Attempted to sendToHost on a Gateway that is not running.");
        return;
    }

}

// Local Variables:
// tab-width: 8
// mode: C++
// c-basic-offset: 4
// indent-tabs-mode: t
// c-file-style: "stroustrup"
// End:
// ex: shiftwidth=4 tabstop=8
