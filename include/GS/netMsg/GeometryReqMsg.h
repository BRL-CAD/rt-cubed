/*                G E O M E T R Y R E Q M S G . H
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
/** @file GeometryReqMsg.h
 *
 * Brief description
 *
 */

#ifndef __GEOMETRYREQMSG_H__
#define __GEOMETRYREQMSG_H__

#include "iBME/iBMECommon.h"
#include "GE/io/DataStream.h"
#include "GS/netMsg/NetMsg.h"

class GeometryReqMsg : public NetMsg
    {

    public:

      //Only Constructor
      GeometryReqMsg(unsigned int mType, UUID mUUID, UUID rUUID, unsigned char v, std::string d);

      //Deserializing Constructors
      GeometryReqMsg(unsigned char data[], unsigned int len);
      GeometryReqMsg(DataStream* ds);

      //Destructor
      virtual ~GeometryReqMsg();
  
      virtual std::string toString();

      /*
       *Getters n Setters
       */
	unsigned char getReqType();
	void setReqType(unsigned char v);

	std::string getData();
	void setData(std::string v);


    private:
      unsigned char reqType;
      std::string data;
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
