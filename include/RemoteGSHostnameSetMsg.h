/*             R E M O T E G S H O S T N A M E S E T M S G  . H
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
/** @file RemoteGSHostnameSetMsg.cxx
 *
 * Brief description
 *
 */

#ifndef __REMOTEGSHOSTNAMESETMSG_H__
#define __REMOTEGSHOSTNAMESETMSG_H__

#include "GenericOneStringMsg.h"

class RemoteGSHostnameSetMsg: public GenericOneStringMsg
{

public:

	//Normal Constructor
	RemoteGSHostnameSetMsg(QString s);

	//Reply Constructor
	RemoteGSHostnameSetMsg(RemoteGSHostnameSetMsg* msg, QString s);

	//Deserializing Constructors
	RemoteGSHostnameSetMsg(QDataStream* ds, QString origin);

	//Destructor
	virtual ~RemoteGSHostnameSetMsg();

	QString getRemoteGSHostname();
};

#endif //__REMOTEGSHOSTNAMESETMSG_H__
// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
