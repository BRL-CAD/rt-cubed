/*         R E M H O S T N A M E S E T M S G . H
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

/** @file RemHostNameSetMsg.h
 *
 *  Description -
 *      
 *
 *  Author - David Loman
 *
 */

#if !defined(_REMHOSTNAMESETMSG_H_)
#define _REMHOSTNAMESETMSG_H_

#include "iBME/iBMECommon.h"
#include "io/DataInputStream.h"
#include "io/DataOutputStream.h"
#include "io/ByteArrayOutputStream.h"
#include "io/ByteArrayInputStream.h"
#include "GeometryService/NetMsg.h"


class RemHostNameSetMsg : public NetMsg
    {

    public:

      //Only Constructor
      RemHostNameSetMsg(uInt mType, UUID mUUID, UUID rUUID, String v);

      //Deserializing Constructors
      RemHostNameSetMsg(array<uByte>* data);
      RemHostNameSetMsg(DataInputStream* dis);

      //Destructor
      virtual ~RemHostNameSetMsg();
  
      virtual String toString();

      /*
       *Getters n Setters
       */
	String getHostName();
	void setHostName(String v);


    private:
      String hostname;
      virtual bool _deserialize(DataInputStream* dis);
      virtual bool _serialize(DataOutputStream* dos);

    };

#endif // !defined(_REMHOSTNAMESETMSG_H_)

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
