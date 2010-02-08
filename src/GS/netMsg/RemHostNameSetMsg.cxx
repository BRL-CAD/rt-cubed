/*             R E M H O S T N A M E S E T M S G . C X X
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
/** @file RemHostNameSetMsg.cxx
 *
 * Brief description
 *
 */

#include "GS/netMsg/RemHostNameSetMsg.h"
#include <sstream>

//Normal Constructor
RemHostNameSetMsg::RemHostNameSetMsg(QString hostname):
  GenericOneStringMsg(REMHOSTNAMESET, hostname)
{
}

  //Reply Constructor
RemHostNameSetMsg::RemHostNameSetMsg(RemHostNameSetMsg* msg, QString hostname):
  GenericOneStringMsg(REMHOSTNAMESET, msg, hostname)
{
}

//Deserializing Constructor
RemHostNameSetMsg::RemHostNameSetMsg(QDataStream* ds):
  GenericOneStringMsg(ds)
{
}

//Destructor
RemHostNameSetMsg::~RemHostNameSetMsg()
{
}

 /*
 *Getters n Setters
 */
QString RemHostNameSetMsg::getRemoteHostName() {return this->strData;}

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
