/*             N E W H O S T O N N E T M S G . H
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
/** @file NewHostOnNetMsg.h
 *
 * Brief description
 *
 */

#ifndef __NEWHOSTONNETMSG_H__
#define __NEWHOSTONNETMSG_H__

#include "GenericOneStringMsg.h"

class NewHostOnNetMsg: public GenericOneStringMsg
{

public:
	/* Normal Constructor */
	NewHostOnNetMsg(QString s);

	/* Reply Constructor */
	NewHostOnNetMsg(NetMsg* msg, QString gsHostname);

	/* Deserializing Constructor */
	NewHostOnNetMsg(QDataStream* ds, Portal* origin);

	/* Destructor */
	virtual ~NewHostOnNetMsg();

	QString getNewGSHostname();
};

#endif

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8