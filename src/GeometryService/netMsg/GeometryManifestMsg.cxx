/*                  G E O M E T R Y M A N I F E S T M S G . C X X 
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

/** @file GeometryManifestMsg.cxx
 *
 *  Description -
 *      
 *
 *  Author - David Loman
 *
 */

#include "GeometryService/netMsg/GeometryManifestMsg.h"
#include <sstream>

//HeaderOnly Constructor
GeometryManifestMsg::GeometryManifestMsg(uInt mType, String mUUID, String rUUID):
  NetMsg(mType, mUUID, rUUID)
{
  this->itemData = new std::vector<String>();

}

//Deserializing Constructors
GeometryManifestMsg::GeometryManifestMsg(DataStream* ds)
{
  this->deserialize(ds);
}
GeometryManifestMsg::GeometryManifestMsg(uByte* data, uInt len)
{
  DataStream ds;
  for (uInt i = 0; i < len; i++)
    {
      ds << data[i];
    }
  this->deserialize(&ds);
}

//Destructor
GeometryManifestMsg::~GeometryManifestMsg()
{
}


bool GeometryManifestMsg::_deserialize(DataStream* ds)
{
  uInt numOfItems = ds->readUInt();
  std::string s;

  for (uInt i = 0; i < numOfItems; ++i)
    {
      s = ds->readString();
      this->itemData->push_back(s);
    }
  return true;
}

bool GeometryManifestMsg::_serialize(DataStream* ds)
{
  ds->writeUInt((uInt)this->itemData->size());

  std::vector<String>::const_iterator cii;
  for(cii=this->itemData->begin(); cii!=this->itemData->end(); cii++)
    {
      ds->writeString(*cii);
    }
  /*

  for (uInt i = 0; i< this->itemData->size(); ++i)
  {
      
  ds->writeString(this->itemData[i]);
  }
  */
  return true;
}

String GeometryManifestMsg::toString() 
{
  std::stringstream Num;
  Num << "msgType: " << this->msgType << " \t";   
  Num << "msgUUID: " << this->msgUUID << " \t";
  Num << "reUUID: " << this->reUUID << " \t\n";
  Num << "\t\titemData.size(): " << this->itemData->size();
  Num << "\n";

  std::vector<String>::const_iterator cii;
  for(cii=this->itemData->begin(); cii!=this->itemData->end(); cii++)
    {
      Num  << "\t\t" << *cii << "\n";
    }
  Num << "\n";

  return Num.str();
}

/*
 *Getters n Setters
 */
uInt GeometryManifestMsg::getNumOfItems() {return this->itemData->size();}

std::vector<String>* GeometryManifestMsg::getItemData() {return this->itemData;}

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
