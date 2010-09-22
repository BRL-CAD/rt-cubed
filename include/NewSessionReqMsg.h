/*            N E W S E S S I O N R E Q M S G . H
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
/** @file NewSessionReqMsg.h
 *
 * Brief description
 *
 */

#ifndef __NEWSESSIONREQMSG_H__
#define __NEWSESSIONREQMSG_H__

#include "NetMsg.h"

class NewSessionReqMsg: public NetMsg
{

public:

	/* Normal Constructor */
	NewSessionReqMsg(QString uname, QString passwd);

	/* Reply Constructor */
	NewSessionReqMsg(NetMsg* msg, QString uname, QString passwd);

	/* Deserializing Constructor */
	NewSessionReqMsg(QDataStream* ds, Portal* origin);

	/* Destructor */
	virtual ~NewSessionReqMsg();

	/*
	 * Utilities
	 */
	virtual QString toString();
	QString getUName();
	QString getPasswd();

protected:
	QString uname;
	QString passwd;

	virtual bool _serialize(QDataStream* ds);
	virtual bool _equals(const NetMsg& msg);
};

#endif //__NEWSESSIONREQMSG_H__
// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
