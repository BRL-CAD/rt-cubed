/*         R E M H O S T N A M E S E T F A I L M S G . C X X
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

/** @file RemHostNameSetFailMsg.cxx
 *
 *  Description -
 *      
 *
 *  Author - David Loman
 *
 */

#include "GS/netMsg/RemHostNameSetFailMsg.h"
#include <sstream>

//HeaderOnly Constructor
RemHostNameSetFailMsg::RemHostNameSetFailMsg(unsigned int mType, UUID  mUUID, UUID rUUID, unsigned char v):
  NetMsg(mType, mUUID, rUUID), failureCode(v)
{
}

//Deserializing Constructors
RemHostNameSetFailMsg::RemHostNameSetFailMsg(DataStream* ds)
{
  this->deserialize(ds);
}
RemHostNameSetFailMsg::RemHostNameSetFailMsg(unsigned char data[], unsigned int len)
{
  DataStream ds;
  for (int i = 0; i < len; i++)
    {
      ds << data[i];
    }
  this->deserialize(&ds);
}

//Destructor
RemHostNameSetFailMsg::~RemHostNameSetFailMsg()
{
}


bool RemHostNameSetFailMsg::_deserialize(DataStream* ds)
{
  *ds >> this->failureCode;
  return true;
}

bool RemHostNameSetFailMsg::_serialize(DataStream* ds)
{
  *ds << this->failureCode;
  return true;
}

/*
 *Getters n Setters
 */
unsigned char RemHostNameSetFailMsg::getFailureCode() {return this->failureCode;}
void  RemHostNameSetFailMsg::setFailureCode(unsigned char v)
{
  this->msgLen = v;
}

std::string RemHostNameSetFailMsg::toString() 
{
  std::stringstream Num;
  Num << "msgType: " << this->msgType << " \t";   
  Num << "msgUUID: " << this->msgUUID << " \t";
  Num << "reUUID: " << this->reUUID << " \t";
  Num << "FailureCode: " << static_cast<unsigned int>(this->failureCode);
  Num << "\n";
  return Num.str();
}

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
