/*         R E M H O S T N A M E S E T M S G . H
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
#include "GE/io/DataInputStream.h"
#include "GE/io/DataOutputStream.h"
#include "GE/io/ByteArrayOutputStream.h"
#include "GE/io/ByteArrayInputStream.h"
#include "GS/netMsg/NetMsg.h"


class RemHostNameSetMsg : public NetMsg
    {

    public:

      //Only Constructor
      RemHostNameSetMsg(unsigned int mType, UUID mUUID, UUID rUUID, std::string v);

      //Deserializing Constructors
      RemHostNameSetMsg(unsigned char data[], unsigned int len);
      RemHostNameSetMsg(DataStream* ds);

      //Destructor
      virtual ~RemHostNameSetMsg();
  
      virtual std::string toString();

      /*
       *Getters n Setters
       */
	std::string getHostName();
	void setHostName(std::string v);


    private:
      std::string hostname;
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
