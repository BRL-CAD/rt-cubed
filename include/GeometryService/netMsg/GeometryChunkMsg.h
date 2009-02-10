/*          G E O M E T R Y C H U N K M S G. H
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

/** @file GeometryChunkMsg.h
 *
 *  Description -
 *      
 *
 *  Author - David Loman
 *
 */

#if !defined(_GEOMETRYCHUNKMSG_H_)
#define _GEOMETRYCHUCKMSG_H_

#include "iBME/iBMECommon.h"
#include "io/DataInputStream.h"
#include "io/DataOutputStream.h"
#include "io/ByteArrayOutputStream.h"
#include "io/ByteArrayInputStream.h"
#include "GeometryService/netMsg/NetMsg.h"


class GeometryChunkMsg : public NetMsg
    {

    public:

      //Only Constructor
      GeometryChunkMsg(uInt mType, String mUUID, String rUUID, uByte* ba, uInt len);

      //Deserializing Constructors
      GeometryChunkMsg(DataStream* ds);

      //Destructor
      virtual ~GeometryChunkMsg();
  
      virtual String toString();

      /*
       *Getters n Setters
       */
      uByte* getData();
      void setData(const uByte* v, const uInt vLen);

      uInt getDataLen();


    private:
      uByte* data;
      uInt dataLen;

      virtual bool _deserialize(DataStream* ds);
      virtual bool _serialize(DataStream* ds);

    };

#endif // !defined(_REMHOSTNAMESETMSG_H_)

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
