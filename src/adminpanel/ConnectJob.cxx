/*                  C O N N E C T J O B . C X X
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
/** @file ConnectJob.cxx
 *
 * Brief description
 *
 */

#include "ConnectJob.h"
#include "GS/GSCommon.h"
#include <QHostAddress>

ConnectJob::ConnectJob(NetPortalManager* portMan, QHostAddress address, quint16 port)
{
	this->portMan = portMan;
	this->address = address;
	this->port = port;
}
ConnectJob::~ConnectJob()
{
}

JobResult ConnectJob::_doJob()
{
	NetPortal* portal = this->portMan->getNewPortal();
	portal->connectToNetHost(this->address, this->port);

	return JOB_COMPLETED_NO_ERRORS;
}

// Local Variables:
// tab-width: 8
// mode: C++
// c-basic-offset: 4
// indent-tabs-mode: t
// c-file-style: "stroustrup"
// End:
// ex: shiftwidth=4 tabstop=8
