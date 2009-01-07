/*                      N E T M S G . H
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

/** @file NetMsg.h
 *
 *  Description -
 *      
 *
 *  Author - David Loman
 *
 */

#if !defined(_NETMSG_H_)
#define _NETMSG_H_

#include "iBME/iBMECommon.h"
#include "io/DataInputStream.h"
#include "io/DataOutputStream.h"
#include "io/ByteArrayOutputStream.h"
#include "io/ByteArrayInputStream.h"

    class NetMsg
    {

    public:

      //Default Constructor
      NetMsg();

      //HeaderOnly Constructor
      NetMsg(uInt mType, UUID mUUID, UUID rUUID);

      //Deserializing Constructors
      NetMsg(array<uByte>* data);
      NetMsg(DataInputStream* dis);

      //Destructor
      virtual ~NetMsg();
  

      //Serializers
      array<uByte>* serialize();
      void serialize(DataOutputStream* dos);

      /*
       *Getters n Setters
       */
      uInt getMsgLen();
      uInt getMsgType();
      UUID getMsgUUID();
      UUID getReUUID();

      void setMsgLen(uInt v);
      void setMsgType(uInt v);
      void setMsgUUID(UUID v);
      void setReUUID(UUID v);

      virtual String toString();
      void printMe();

    private:
      uInt msgLen;
      uInt msgType;
      UUID msgUUID;
      UUID reUUID;
      array<uByte> data;

      void deserialize(DataInputStream* dis);

      virtual bool _deserialize(DataInputStream* dis);
      virtual bool _serialize(DataOutputStream* dos);

    };

#endif // !defined(_NETMSG_H_)

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
