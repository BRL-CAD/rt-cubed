/*                    C O N N E C T J O B . H
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
/** @file ConnectJob.h
 *
 * Brief description
 *
 */

#ifndef __CONNECTJOB_H__
#define __CONNECTJOB_H__

#include "GS/netMsg/NetMsg.h"
#include "GS/Jobs/AbstractJob.h"
#include "GS/NetPortalManager.h"

#include <QString>
#include <QStringList>
#include <QHostAddress>

class ConnectJob : public AbstractJob
{
public:
	ConnectJob(NetPortalManager* portMan, QHostAddress address, quint16 port);
	virtual ~ConnectJob();

protected:
	virtual JobResult _doJob();

private:
	NetPortalManager* portMan;
	QHostAddress address;
	quint16 port;
};

#endif

/*
 * Local Variables:
 * tab-width: 8
 * mode: C
 * indent-tabs-mode: t
 * c-file-style: "stroustrup"
 * End:
 * ex: shiftwidth=4 tabstop=8
 */
