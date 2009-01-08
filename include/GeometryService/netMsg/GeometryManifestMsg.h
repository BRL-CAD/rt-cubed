/*                  G E O M E T R Y R E Q M S G. H
 * BRL-CAD
 *
 * Copyright (c) 1997-2008 United States Government as represented by
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

/** @file GeometryManifestMsg.h
 *
 *  Description -
 *      
 *
 *  Author - David Loman
 *
 */

#if !defined(_GEOMETRYMANIFESTMSG_H_)
#define _GEOMETRYMANIFESTMSG_H_

#include "iBME/iBMECommon.h"
#include "io/DataInputStream.h"
#include "io/DataOutputStream.h"
#include "io/ByteArrayOutputStream.h"
#include "io/ByteArrayInputStream.h"
#include "GeometryService/NetMsg.h"


class GeometryManifestMsg : public NetMsg
    {

    public:

      //Only Constructor
      GeometryManifestMsg(uInt mType, UUID mUUID, UUID rUUID, uByte v, array<uByte>* d);

      //Deserializing Constructors
      GeometryManifestMsg(array<uByte>* data);
      GeometryManifestMsg(DataInputStream* dis);

      //Destructor
      virtual ~GeometryManifestMsg();
  
      virtual String toString();

      /*
       *Getters n Setters
       */
	uByte getReqType();
	void setReqType(uByte v);

	array<uByte>* getData();
	void setData(array<uByte>* v);


    private:
      uByte reqType;
      array<uByte>* data;
      virtual bool _deserialize(DataInputStream* dis);
      virtual bool _serialize(DataOutputStream* dos);

    };

#endif // !defined(_GEOMETRYMANIFESTMSG_H_)

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
