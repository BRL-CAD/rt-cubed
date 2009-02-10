/*         G E O M E T R Y C H U N K M S G . C X X
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

/** @file GeometryChunkMsg.cxx
 *
 *  Description -
 *      
 *
 *  Author - David Loman
 *
 */

#include "GeometryService/netMsg/GeometryChunkMsg.h"
#include <sstream>

//HeaderOnly Constructor
GeometryChunkMsg::GeometryChunkMsg(uInt mType, String mUUID, String rUUID, uByte* ba, uInt  len):
  NetMsg(mType, mUUID, rUUID)
{
  this->setData(ba, len);

}

//Deserializing Constructors
GeometryChunkMsg::GeometryChunkMsg(DataStream* ds)
{
  this->deserialize(ds);
}

//Destructor
GeometryChunkMsg::~GeometryChunkMsg()
{
  delete data;
}


bool GeometryChunkMsg::_deserialize(DataStream* ds)
{
  this->dataLen = ds->readUInt();
  this->data = new uByte[this->dataLen];

  uInt actualRead = ds->readUByteArray(this->data, this->dataLen);

  if (actualRead != this->dataLen) {
    std::cerr << "There was an error in GeometryChunkMsg.setData()\n";
  }

  return true;
}

bool GeometryChunkMsg::_serialize(DataStream* ds)
{
  ds->writeUInt(this->dataLen);
  ds->writeUByteArray(this->data, this->dataLen);
  return true;
}

String GeometryChunkMsg::toString() 
{
  std::stringstream Num;
  Num << "msgType: " << this->msgType << " \t";   
  Num << "msgUUID: " << this->msgUUID << " \t";
  Num << "reUUID: " << this->reUUID << " \t";
  Num << "dataLen: " << this->dataLen << " \t";
  Num << "data: " << this->data ;
  Num << "\n";
  return Num.str();
}

 /*
 *Getters n Setters
 */
uByte* GeometryChunkMsg::getData() {return this->data;}
uint GeometryChunkMsg::getDataLen(){return this->dataLen;}

void GeometryChunkMsg::setData(const uByte* v, const uInt vLen)
{
  uByte* pv = (uByte*)v;

  this->data = new uByte[vLen];
  this->dataLen = vLen;
  
  for (uInt i = 0; i < this->dataLen; ++i)
    {
      this->data[i] = *pv;
      pv++;
    }
}




// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
