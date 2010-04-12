/*        N E T M S G S U B S C R I B E R R E G I S T R Y . C X X
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
/** @file NetMsgSubscriberRegistry.cxx
 *
 * Provides a means for any class implementing the
 * INetMsgHandler interface to be registered onto
 * the NetMsg distribution lists.
 *
 */

#include "GS/libNetwork/NetMsgSubscriberRegistry.h"
#include <cstdlib>

NetMsgSubscriberRegistry* NetMsgSubscriberRegistry::pInstance = NULL;

NetMsgSubscriberRegistry::NetMsgSubscriberRegistry()
{
	// TODO Auto-generated constructor stub

}

NetMsgSubscriberRegistry::~NetMsgSubscriberRegistry()
{
	// TODO Auto-generated destructor stub
}

NetMsgSubscriberRegistry* NetMsgSubscriberRegistry::getInstance()
{
	if (!NetMsgSubscriberRegistry::pInstance)
	{
		NetMsgSubscriberRegistry::pInstance = new NetMsgSubscriberRegistry();
	}
	return NetMsgSubscriberRegistry::pInstance;
}

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
