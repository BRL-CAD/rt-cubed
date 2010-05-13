/*             G E N E R I C O N E B Y T E M S G . H
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
/** @file GenericOneByteMsg.h
 *
 * Brief description
 *
 */

#ifndef __GENERICONEBYTEMSG_H__
#define __GENERICONEBYTEMSG_H__

#include "NetMsg.h"

class GenericOneByteMsg: public NetMsg
{

public:

	/* Normal Constructor */
	GenericOneByteMsg(quint32 type, quint8 b);

	/* Reply Constructor */
	GenericOneByteMsg(quint32 type, NetMsg* msg, quint8 b);

	/* Deserializing Constructor */
	GenericOneByteMsg(QDataStream* ds, QString origin);

	/* Destructor */
	virtual ~GenericOneByteMsg();

	/*
	 * Utilities
	 */
	virtual QString toString();

protected:
	quint8 getData();
	quint8 data;

	virtual bool _serialize(QDataStream* ds);
	virtual bool _equals(const NetMsg& msg);
};

#endif

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
