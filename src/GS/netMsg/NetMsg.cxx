/*                      N E T M S G . C X X
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
/** @file NetMsg.cxx
 *
 * Brief description
 *
 */

#include "GS/netMsg/NetMsg.h"
#include <sstream>

//Default Constructor
NetMsg::NetMsg()
{
}

//HeaderOnly Constructor
NetMsg::NetMsg(unsigned int mType, UUID mUUID, UUID rUUID):
  msgType(mType), msgUUID(mUUID), reUUID(rUUID)
{
}

//Deserializing Constructors
NetMsg::NetMsg(DataStream* ds)
{
  this->deserialize(ds);
}
NetMsg::NetMsg(unsigned char data[], unsigned int len)
{
  DataStream ds;

  for (int i = 0; i < len; i++)
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
    this->msgType = ds->readUInt();
    this->msgUUID = ds->readString();
    this->reUUID = ds->readString();

    if (!this->_deserialize(ds))
      {
	//Error here.
      }
  } catch (IOException ioe) {
    std::cerr << "Error in NetMsg(): " << ioe.getMessage() << std::endl;
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
unsigned int NetMsg::getMsgLen() {return this->msgLen;}
void NetMsg::setMsgLen(unsigned int v)
{
  this->msgLen = v;
}

unsigned int NetMsg::getMsgType(){return this->msgType;}
void NetMsg::setMsgType(unsigned int v)
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



std::string NetMsg::toString() 
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
  std::string s = this->toString();
  std::cout << s;
}



// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
