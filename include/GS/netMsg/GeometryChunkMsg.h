/*              G E O M E T R Y C H U N K M S G . H
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
/** @file GeometryChunkMsg.h
 *
 * Brief description
 *
 */

#ifndef _GEOMETRYCHUNKMSG_H_
#define _GEOMETRYCHUCKMSG_H_

#include "iBME/iBMECommon.h"
#include "GE/io/DataInputStream.h"
#include "GE/io/DataOutputStream.h"
#include "GE/io/ByteArrayOutputStream.h"
#include "GE/io/ByteArrayInputStream.h"
#include "GS/netMsg/NetMsg.h"


class GeometryChunkMsg : public NetMsg
    {

    public:

      //Only Constructor
      GeometryChunkMsg(unsigned int mType, UUID mUUID, UUID rUUID, unsigned char* ba, unsigned int len);

      //Deserializing Constructors
      GeometryChunkMsg(DataStream* ds);

      //Destructor
      virtual ~GeometryChunkMsg();
  
      virtual std::string toString();

      /*
       *Getters n Setters
       */
      unsigned char* getData();
      void setData(const unsigned char* v, const unsigned int vLen);

      unsigned int getDataLen();


    private:
      unsigned char* data;
      unsigned int dataLen;

      virtual bool _deserialize(DataStream* ds);
      virtual bool _serialize(DataStream* ds);

    };

#endif

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
