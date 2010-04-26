/*             R E M O T E G S H O S T N A M E S E T M S G . C X X
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

#include "libNetwork/RemoteGSHostnameSetMsg.h"
#include <sstream>

//Normal Constructor
RemoteGSHostnameSetMsg::RemoteGSHostnameSetMsg(QString gsHostname):
  GenericOneStringMsg(REMGSHOSTNAMESET, gsHostname)
{
}

  //Reply Constructor
RemoteGSHostnameSetMsg::RemoteGSHostnameSetMsg(RemoteGSHostnameSetMsg* msg, QString gsHostname):
  GenericOneStringMsg(REMGSHOSTNAMESET, msg, gsHostname)
{
}

//Deserializing Constructor
RemoteGSHostnameSetMsg::RemoteGSHostnameSetMsg(QDataStream* ds):
  GenericOneStringMsg(ds)
{
}

//Destructor
RemoteGSHostnameSetMsg::~RemoteGSHostnameSetMsg()
{
}

 /*
 *Getters n Setters
 */
QString RemoteGSHostnameSetMsg::getRemoteGSHostname() {return this->strData;}

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
