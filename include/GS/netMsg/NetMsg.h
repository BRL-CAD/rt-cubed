/*                      N E T M S G . H
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
#include "io/DataStream.h"

class NetMsg
{

public:

  //Default Constructor
  NetMsg();

  //HeaderOnly Constructor
  NetMsg(unsigned int mType, UUID mUUID, UUID rUUID);

  //Deserializing Constructors
  NetMsg(unsigned char data[], unsigned int len);
  NetMsg(DataStream* ds);

  //Destructor
  virtual ~NetMsg();
  

  //Serializers
  DataStream* serialize();
  void serialize(DataStream* ds);

  /*
   *Getters n Setters
   */
  unsigned int getMsgLen();
  unsigned int getMsgType();
  UUID getMsgUUID();
  UUID getReUUID();

  void setMsgLen(unsigned int v);
  void setMsgType(unsigned int v);
  void setMsgUUID(UUID v);
  void setReUUID(UUID v);

  virtual std::string toString();
  void printMe();

protected:
  unsigned int msgLen;
  unsigned int msgType;
  UUID msgUUID;
  UUID reUUID;

  void deserialize(DataStream* ds);

  virtual bool _deserialize(DataStream* ds);
  virtual bool _serialize(DataStream* ds);

};

#endif // !defined(_NETMSG_H_)

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
