/*             N E W H O S T O N N E T M S G . C X X
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
/** @file NewHostOnNetMsg.cxx
 *
 * Brief description
 *
 */

#include "NetMsgTypes.h"
#include "NewHostOnNetMsg.h"
#include <sstream>

//Normal Constructor
NewHostOnNetMsg::NewHostOnNetMsg(QString gsHostname) :
    GenericOneStringMsg(REMGSHOSTNAMESET, gsHostname)
{
}

//Reply Constructor
NewHostOnNetMsg::NewHostOnNetMsg(NewHostOnNetMsg* msg, QString gsHostname) :
    GenericOneStringMsg(REMGSHOSTNAMESET, msg, gsHostname)
{
}

NewHostOnNetMsg::NewHostOnNetMsg(QDataStream* ds, QString origin) :
    GenericOneStringMsg(ds, origin)
{
}

//Destructor
NewHostOnNetMsg::~NewHostOnNetMsg()
{
}

/*
 *Getters n Setters
 */
QString NewHostOnNetMsg::getNewGSHostname()
{
    return this->strData;
}

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
