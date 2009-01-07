/*                      N E T M S G . C X X
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

/** @file NetMsg.cxx
 *
 *  Description -
 *      
 *
 *  Author - David Loman
 *
 */

#include "GeometryService/NetMsg.h"

//Default Constructor
NetMsg::NetMsg()
{
}

//HeaderOnly Constructor
NetMsg::NetMsg(uInt mLen, uInt mType, String mUUID, String rUUID):
  msgLen(mLen), msgType(mType), msgUUID(mUUID), reUUID(rUUID)
{
}

//Deserializing Constructor
NetMsg::NetMsg(DataInputStream dis)
{
}

//Destructor
NetMsg::~NetMsg()
{
}


//Serializers
array<uByte>* NetMsg::serialize()
{
  ByteArrayOutputStream* baos = new ByteArrayOutputStream();
  DataOutputStream* dos = new DataOutputStream(*baos);

  this->serialize(dos);
  array<uByte>* pa = baos->toByteArray();

  delete dos;
  delete baos;

  return pa;
}

void NetMsg::serialize(DataOutputStream* dos)
{
  //TODO implement serialization here.
}

void NetMsg::_deserialize()
{
}

void NetMsg::_serialize(DataOutputStream* dos)
{
}

/*
 *Getters n Setters
 */
uInt NetMsg::getMsgLen() {return this->msgLen;}
uInt NetMsg::getMsgType(){return this->msgType;}
UUID NetMsg::getMsgUUID(){return this->msgUUID;}
UUID NetMsg::getReUUID() {return this->reUUID;}

void NetMsg::setMsgLen(uInt v)
{
}
void NetMsg::setMsgType(uInt v)
{
}
void NetMsg::setMsgUUID(UUID v)
{
}
void NetMsg::setReUUID(UUID v)
{
}

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
