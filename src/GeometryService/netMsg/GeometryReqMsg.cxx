/*                  G E O M E T R Y R E Q M S G . C X X 
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

/** @file GeometryReqMsg.cxx
 *
 *  Description -
 *      
 *
 *  Author - David Loman
 *
 */

#include "GeometryService/netMsg/GeometryReqMsg.h"
#include <sstream>

//HeaderOnly Constructor
GeometryReqMsg::GeometryReqMsg(uInt mType, String mUUID, String rUUID, uByte v, String d):
  NetMsg(mType, mUUID, rUUID), reqType(v), data(d)
{
}

//Deserializing Constructors
GeometryReqMsg::GeometryReqMsg(DataStream* ds)
{
  this->deserialize(ds);
}
GeometryReqMsg::GeometryReqMsg(uByte data[], uInt len)
{
  DataStream ds;
  for (uInt i = 0; i < len; i++)
    {
      ds << data[i];
    }
  this->deserialize(&ds);
}

//Destructor
GeometryReqMsg::~GeometryReqMsg()
{
}


bool GeometryReqMsg::_deserialize(DataStream* ds)
{
  *ds >> this->reqType;
  *ds >> this->data;

  return true;
}

bool GeometryReqMsg::_serialize(DataStream* ds)
{
  *ds << this->reqType;
  *ds << this->data;
  return true;
}

String GeometryReqMsg::toString() 
{
  std::stringstream Num;
  Num << "msgType: " << this->msgType << " \t";   
  Num << "msgUUID: " << this->msgUUID << " \t";
  Num << "reUUID: " << this->reUUID << " \t";
  Num << "ReqType: " << (uInt)this->reqType << " \t";
  Num << "LenOfData: " << this->data.size() << " \t";
  Num << "Data: " << this->data;
  Num << "\n";
  return Num.str();
}

/*
 *Getters n Setters
 */
uByte GeometryReqMsg::getReqType() {return this->reqType;}
void GeometryReqMsg::setReqType(uByte v)
{
  this->reqType = v;
}

String GeometryReqMsg::getData() {return this->data;}
void GeometryReqMsg::setData(String v)
{
  this->data = v;
}


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
