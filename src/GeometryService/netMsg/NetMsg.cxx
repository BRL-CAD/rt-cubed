/*                      N E T M S G . C X X
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
NetMsg::NetMsg(DataStream* ds)
{
  this->deserialize(ds);
}
NetMsg::NetMsg(uByte data[], uInt len)
{
  DataStream ds;

  for (uInt i = 0; i < len; i++)
    {
      ds << data[i];
    }

  this->deserialize(&ds);
}


//Destructor
NetMsg::~NetMsg()
{
}


//Serializers
DataStream* NetMsg::serialize()
{
  DataStream* pds = new DataStream();

  this->serialize(pds); 

  return pds;
}

void NetMsg::serialize(DataStream* pds)
{
  //Make a Temp DS
  DataStream* tds = new DataStream;;

  //Serialize Header
  *tds << this->msgType;
  *tds << this->msgUUID;
  *tds << this->reUUID;

  //Call Serialize subroutine for subclassess.
  if (!this->_serialize(tds))
    {
      //Error here.
    }

  //write the length of tds and then the contents of tds 
  *pds << tds->getBytesFilled();
  *pds << *tds;

  delete tds;
}

void NetMsg::deserialize(DataStream* ds)
{
  try {
    //deserialize Header
    *ds >> this->msgType;
    *ds >> this->msgUUID;
    *ds >> this->reUUID;
  } catch (IOException ioe) {
    std::cerr << "Error: " << ioe.getMessage() << std::endl;
  }

  if (!this->_deserialize(ds))
    {
      //Error here.
    }
}



bool NetMsg::_deserialize(DataStream* ds)
{
  return true;
}

bool NetMsg::_serialize(DataStream* ds)
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
  Num << "msgType: '" << this->msgType << "' \t";
  Num << "msgUUID: '" << this->msgUUID << "' \t";
  Num << "reUUID: '" << this->reUUID << "'";
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
