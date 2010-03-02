/*             G E N E R I C T W O B Y T E S M S G . H
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
/** @file GenericTwoBytesMsg.h
 *
 * Brief description
 *
 */

#ifndef __GENERICTWOBYTESMSG_H__
#define __GENERICTWOBYTESMSG_H__

#include "GS/GSCommon.h"
#include "GS/libNetwork/NetMsg.h"

class GenericTwoBytesMsg : public NetMsg
{

public:

  //Normal Constructor
  GenericTwoBytesMsg(quint32 type, quint16 b);

  //Reply Constructor
  GenericTwoBytesMsg(quint32 type, NetMsg* msg, quint16 b);

  //Deserializing Constructors
  GenericTwoBytesMsg(QDataStream* ds);

  //Destructor
  virtual ~GenericTwoBytesMsg();

  /*
   * Utilities
   */
  virtual QString toString();

protected:
  quint16 getData();
  quint16 data;

  virtual bool _serialize(QDataStream* ds);
  virtual bool _equals(NetMsg& msg);

};

#endif

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
