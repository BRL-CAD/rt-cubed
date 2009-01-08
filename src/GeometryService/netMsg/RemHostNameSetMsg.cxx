/*         R E M H O S T N A M E S E T M S G . C X X
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

/** @file RemHostNameSetMsg.cxx
 *
 *  Description -
 *      
 *
 *  Author - David Loman
 *
 */

#include "GeometryService/netMsg/RemHostNameSetMsg.h"
#include <sstream>

//HeaderOnly Constructor
RemHostNameSetMsg::RemHostNameSetMsg(uInt mType, String mUUID, String rUUID, String v):
  NetMsg(mType, mUUID, rUUID), hostname(v)
{
}

//Deserializing Constructors
RemHostNameSetMsg::RemHostNameSetMsg(DataInputStream* dis)
{
  this->deserialize(dis);
}
RemHostNameSetMsg::RemHostNameSetMsg(array<uByte>* data)
{
  ByteArrayInputStream* bais = new ByteArrayInputStream(*data);
  DataInputStream* dis = new DataInputStream(*bais);

  this->deserialize(dis);

  delete dis;
  delete bais;
}

//Destructor
RemHostNameSetMsg::~RemHostNameSetMsg()
{
}


bool RemHostNameSetMsg::_deserialize(DataInputStream* dis)
{
  this->hostname = dis->readString();
  return true;
}

bool RemHostNameSetMsg::_serialize(DataOutputStream* dos)
{
  dos->writeString(this->hostname);
  return true;
}

String RemHostNameSetMsg::toString() 
{
  std::stringstream Num;
  Num << "msgType: " << this->msgType << " \t";   
  Num << "msgUUID: " << this->msgUUID << " \t";
  Num << "reUUID: " << this->reUUID << " \t";
  Num << "hostname: " << this->hostname;
  Num << "\n";
  return Num.str();
}

 /*
 *Getters n Setters
 */
String RemHostNameSetMsg::getHostName() {return this->hostname;}
void RemHostNameSetMsg::setHostName(String v)
{
  this->hostname = v;
}

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
