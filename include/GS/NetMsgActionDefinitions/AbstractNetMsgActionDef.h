/*       A B S T R A C T N E T M S G A C T I O N D E F . H
 * BRL-CAD
 *
 * Copyright (c) 2009 United States Government as represented by
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
/** @file AbstractNetMsgActionDef.h
 *
 * Brief description
 *
 */

#ifndef _ABSTRACTNETMSGACTIONDEF_H_
#define _ABSTRACTNETMSGACTIONDEF_H_

#include "GS/netMsg/NetMsg.h"
#include "GS/Jobs/AbstractJob.h"

class AbstractNetMsgActionDef
{

	public:
		AbstractNetMsgActionDef();
		virtual ~AbstractNetMsgActionDef();

  		AbstractJob& convert(NetMsg& msg);

	private:
		unsigned int msgType;

};

#endif

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
