/*                 N E T M S G A C T I O N J O B . C X X
 * BRL-CAD
 *
 * Copyright (c) 1997-2009 United States Government as represented by
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

/** @file NetMsgActionJob.cxx
 *
 *  Description -
 *      
 *
 *  Author - David Loman
 *
 */

#include "GS/Jobs/NetMsgActionJob.h"


NetMsgActionJob::NetMsgActionJob()
{
}

NetMsgActionJob::~NetMsgActionJob()
{
}

NetMsgActionJob::NetMsgActionJob(NetMsg& msg)
{
}

/**
 * 1) Performs lookup on NetMsgActionDefManager.actionDefs map
 * 2) Calls AbstractNetMsgActionDef.convert(NetMsg)
 * 3) Obtains reference to AbstractPortal of NetMsg's origin from
 * CommunicationsManager.portals map.
 */
bool NetMsgActionJob::doJob() {
	return false;
}

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
