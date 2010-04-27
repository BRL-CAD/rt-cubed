/*              G E O M E T R Y C H U N K M S G . H
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
/** @file GeometryChunkMsg.h
 *
 * Brief description
 *
 */

#ifndef __GEOMETRYCHUNKMSG_H__
#define __GEOMETRYCHUCKMSG_H__

#include "GS/GSCommon.h"
#include "libNetwork/GenericMultiByteMsg.h"

class GeometryChunkMsg : public GenericMultiByteMsg
{
  
public:

  //Normal Constructor
  GeometryChunkMsg(char* dataIn, quint32 dataInLen);

  //Reply Constructor
  GeometryChunkMsg(NetMsg* msg, char* dataIn, quint32 dataInLen);

  //Deserializing Constructors
  GeometryChunkMsg(QDataStream* ds, QString origin);
  
 };

#endif

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
