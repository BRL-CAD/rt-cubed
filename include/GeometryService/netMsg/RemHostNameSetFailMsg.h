/*         R E M H O S T N A M E S E T F A I L M S G . H
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

/** @file RemHostNameSetFailMsg.h
 *
 *  Description -
 *      
 *
 *  Author - David Loman
 *
 */

#if !defined(_REMHOSTNAMESETFAILMSG_H_)
#define _REMHOSTNAMESETFAILMSG_H_

#include "iBME/iBMECommon.h"
#include "io/DataInputStream.h"
#include "io/DataOutputStream.h"
#include "io/ByteArrayOutputStream.h"
#include "io/ByteArrayInputStream.h"
#include "GeometryService/netMsg/NetMsg.h"


class RemHostNameSetFailMsg : public NetMsg
    {

    public:

      //Only Constructor
      RemHostNameSetFailMsg(unsigned int mType, UUID mUUID, UUID rUUID, unsigned char v);

      //Deserializing Constructors
      RemHostNameSetFailMsg(unsigned char data[], unsigned int len);
      RemHostNameSetFailMsg(DataStream* ds);

      //Destructor
      virtual ~RemHostNameSetFailMsg();
  
      virtual std::string toString();

      /*
       *Getters n Setters
       */
	unsigned char getFailureCode();
	void  setFailureCode(unsigned char v);

    private:
      unsigned char failureCode;
      virtual bool _deserialize(DataStream* ds);
      virtual bool _serialize(DataStream* ds);

    };

#endif // !defined(_REMHOSTNAMESETFAILMSG_H_)

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
