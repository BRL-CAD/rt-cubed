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
GeometryChunkMsg::GeometryChunkMsg(unsigned int mType, UUID mUUID, UUID  rUUID, unsigned char* ba, unsigned int  len):
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
  this->data = new unsigned char[this->dataLen];

  unsigned int actualRead = ds->readUCharArray(this->data, this->dataLen);

  if (actualRead != this->dataLen) {
    std::cerr << "There was an error in GeometryChunkMsg.setData()\n";
  }

  return true;
}

bool GeometryChunkMsg::_serialize(DataStream* ds)
{
  ds->writeUInt(this->dataLen);
  ds->writeUCharArray(this->data, this->dataLen);
  return true;
}

std::string GeometryChunkMsg::toString() 
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
unsigned char* GeometryChunkMsg::getData() {return this->data;}
unsigned int GeometryChunkMsg::getDataLen(){return this->dataLen;}

void GeometryChunkMsg::setData(const unsigned char* v, const unsigned int vLen)
{
  unsigned char* pv = (unsigned char*)v;

  this->data = new unsigned char[vLen];
  this->dataLen = vLen;
  
  for (int i = 0; i < this->dataLen; ++i)
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
