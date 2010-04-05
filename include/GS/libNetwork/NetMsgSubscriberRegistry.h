/*        N E T M S G S U B S C R I B E R R E G I S T R Y . H
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
/** @file NetMsgSubscriberRegistry.h
 *
 * Provides a means for any class implementing the
 * INetMsgHandler interface to be registered onto
 * the NetMsg distribution lists.
 *
 */

#ifndef __NETMSGSUBSCRIBERREGISTRY_H__
#define __NETMSGSUBSCRIBERREGISTRY_H__

class NetMsgSubscriberRegistry {
public:
	NetMsgSubscriberRegistry();
	virtual ~NetMsgSubscriberRegistry();
};

#endif /* __NETMSGSUBSCRIBERREGISTRY_H__ */

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
