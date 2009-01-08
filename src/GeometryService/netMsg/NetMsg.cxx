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

#include "GeometryService/netMsg/NetMsg.h"
#include <sstream>

//Default Constructor
NetMsg::NetMsg()
{
}

//HeaderOnly Constructor
NetMsg::NetMsg(uInt mType, String mUUID, String rUUID):
  msgType(mType), msgUUID(mUUID), reUUID(rUUID)
{
}

//Deserializing Constructors
NetMsg::NetMsg(DataInputStream* dis)
{
  this->deserialize(dis);
}
NetMsg::NetMsg(array<uByte>* data)
{
  ByteArrayInputStream* bais = new ByteArrayInputStream(*data);
  DataInputStream* dis = new DataInputStream(*bais);

  this->deserialize(dis);

  delete dis;
  delete bais;
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
  //Get a temp BAOS and DOS
  ByteArrayOutputStream* baos2 = new ByteArrayOutputStream();
  DataOutputStream* dos2 = new DataOutputStream(*baos2);

  //Serialize Header
  dos2->writeUInt(this->msgType);
  dos2->writeString(this->msgUUID);
  dos2->writeString(this->reUUID);

  if (!this->_serialize(dos2))
    {
      //Error here.
    }

  //Get the total length of the fully serialized object
  uInt len = baos2->size();

  //write the length and THEN object data to the external DOS.
  dos->writeUInt(len);
  array<uByte>* data = baos2->toByteArray();
  dos->write(*data);

  delete data;
  delete dos2;
  delete baos2;
}

void NetMsg::deserialize(DataInputStream* dis)
{
  //Read data len
  //uInt len =  dis->readUInt();

  //deserialize Header
  this->msgType = dis->readUInt();

  this->msgUUID = dis->readString();

  this->reUUID = dis->readString();

  if (!this->_deserialize(dis))
    {
      //Error here.
    }

}

bool NetMsg::_deserialize(DataInputStream* dis)
{
  return true;
}

bool NetMsg::_serialize(DataOutputStream* dos)
{
  return true;
}

/*
 *Getters n Setters
 */
uInt NetMsg::getMsgLen() {return this->msgLen;}
void NetMsg::setMsgLen(uInt v)
{
  this->msgLen = v;
}

uInt NetMsg::getMsgType(){return this->msgType;}
void NetMsg::setMsgType(uInt v)
{
  this->msgType = v;
}

UUID NetMsg::getMsgUUID(){return this->msgUUID;}
void NetMsg::setMsgUUID(UUID v)
{
  this->msgUUID = v;
}

UUID NetMsg::getReUUID() {return this->reUUID;}
void NetMsg::setReUUID(UUID v)
{
  this->reUUID = v;
}



String NetMsg::toString() 
{
  std::stringstream Num;
  Num << "msgType: " << this->msgType << " \t";
  Num << "msgUUID: " << this->msgUUID << " \t";
  Num << "reUUID: " << this->reUUID;
  Num << "\n";
  return Num.str();
}

void NetMsg::printMe()
{
  String s = this->toString();
  std::cout << s;
}



// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
