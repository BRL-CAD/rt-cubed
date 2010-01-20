/*             R E M H O S T N A M E S E T M S G . H
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
/** @file RemHostNameSetMsg.h
 *
 * Brief description
 *
 */

#ifndef __REMHOSTNAMESETMSG_H__
#define __REMHOSTNAMESETMSG_H__

#include "GS/GSCommon.h"
#include "GS/netMsg/GenericOneStringMsg.h"

class RemHostNameSetMsg : public GenericOneStringMsg
{

public:

  //Normal Constructor
  RemHostNameSetMsg(QString s);

  //Reply Constructor
  RemHostNameSetMsg(RemHostNameSetMsg* msg, QString s);

  //Deserializing Constructors
  RemHostNameSetMsg(QDataStream* ds);

  //Destructor
  virtual ~RemHostNameSetMsg();

  QString getRemoteHostName();
};

#endif

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
