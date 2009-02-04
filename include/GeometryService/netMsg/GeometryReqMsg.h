/*                  G E O M E T R Y R E Q M S G. H
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

/** @file GeometryReqMsg.h
 *
 *  Description -
 *      
 *
 *  Author - David Loman
 *
 */

#if !defined(_GEOMETRYREQMSG_H_)
#define _GEOMETRYREQMSG_H_

#include "iBME/iBMECommon.h"
#include "io/DataStream.h"
#include "GeometryService/netMsg/NetMsg.h"


class GeometryReqMsg : public NetMsg
    {

    public:

      //Only Constructor
      GeometryReqMsg(uInt mType, UUID mUUID, UUID rUUID, uByte v, String d);

      //Deserializing Constructors
      GeometryReqMsg(uByte data[], uInt len);
      GeometryReqMsg(DataStream* ds);

      //Destructor
      virtual ~GeometryReqMsg();
  
      virtual String toString();

      /*
       *Getters n Setters
       */
	uByte getReqType();
	void setReqType(uByte v);

	String getData();
	void setData(String v);


    private:
      uByte reqType;
      String data;
      virtual bool _deserialize(DataStream* ds);
      virtual bool _serialize(DataStream* ds);

    };

#endif // !defined(_GEOMETRYREQMSG_H_)

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
